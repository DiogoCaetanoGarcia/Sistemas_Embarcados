// Codigo para criar um dispositivo de escrita em GPIO

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put_user */
#include <linux/init.h>  // Macros used to mark up functions e.g. __init __exit
#include <linux/device.h> // Header to support the kernel Driver Model
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola gpiomod_output driver!");

#define DEVICE_NAME "gpiomod_output"
#define CLASS_NAME  "gpiomod_output_class"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %ld\n", DEVICE_NAME, s, err_val)
#define LED1 4
#define LED1_NAME "LED1"

static struct timer_list blink_timer;
static long int periodo=HZ/5;

static void blink_timer_func(unsigned long data)
{
	gpio_set_value(LED1, data);
	// Agendar proxima execucao
	blink_timer.data = !data; // Inverte o valor do LED
	blink_timer.expires = jiffies + periodo;
	add_timer(&blink_timer);
}

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static int Major;     // Major number para o device driver
static int Minor = 0; // Minor number definido por mim
static int Device_Open = 0;    // Device aberto? Usado para prevenir acesso multiplo ao device
static int Device_Counter = 0; // Contador para saber quantos caracteres foram lidos
static struct class*  gpiomod_output_Class  = NULL; ///< The device-driver class struct pointer
static struct device* gpiomod_output_Device = NULL; ///< The device-driver device struct pointer

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

#define CLEAN_GPIO_DEVICE_CLASS_MAJOR 0
#define CLEAN_DEVICE_CLASS_MAJOR      1
#define CLEAN_DEVICE_MAJOR            2
#define CLEAN_MAJOR                   3
void module_clean_level(unsigned int level)
{
	if(level<1)
	{
		gpio_set_value(LED1, 0);
		gpio_free(LED1);
	}
	if(level<2) // Remove o dispositivo
		device_destroy(gpiomod_output_Class, MKDEV(Major, 0));
	if(level<3) // Desfaz o registro da classe de dispositivo e remove a classe de dispositivo
	{
		class_unregister(gpiomod_output_Class);
		class_destroy(gpiomod_output_Class);
	}
	if(level<4) // Desfaz o registro do major number
		unregister_chrdev(Major, DEVICE_NAME);
}

int init_module(void)
{
	int ret;
	// Obter major number dinamicamente
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if(Major < 0)
	{
		MSG_BAD("erro ao registrar GPIO device", (long int)Major);
		return Major;
	}
	MSG_OK("registrado corretamente");
	// Registrar a classe do dispositivo
	gpiomod_output_Class = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(gpiomod_output_Class)) // Se houve erro no registro
	{
		module_clean_level(CLEAN_MAJOR);
		MSG_BAD("falhou em registrar a classe do dispositivo", PTR_ERR(gpiomod_output_Class));
		return PTR_ERR(gpiomod_output_Class); // Correct way to return an error on a pointer
	}
	MSG_OK("classe do dispositivo registrada corretamente");

	// Registrar o device driver
	gpiomod_output_Device = device_create(gpiomod_output_Class, NULL, MKDEV(Major, Minor), NULL, DEVICE_NAME);
	if(IS_ERR(gpiomod_output_Device)) // Se houve erro no registro
	{
		module_clean_level(CLEAN_DEVICE_MAJOR);
		MSG_BAD("falhou em criar o device driver", PTR_ERR(gpiomod_output_Device));
		return PTR_ERR(gpiomod_output_Device);
	}
	MSG_OK("dispositivo criado corretamente");
	ret = gpio_request_one(LED1, GPIOF_OUT_INIT_LOW, LED1_NAME);
	if(ret)
	{
		module_clean_level(CLEAN_DEVICE_CLASS_MAJOR);
		MSG_BAD("não conseguiu acesso ao GPIO", (long int)ret);
		return ret;
	}
	MSG_OK("obteve acesso ao GPIO");
	init_timer(&blink_timer);
	blink_timer.function = blink_timer_func;
	blink_timer.data = 1L;
	blink_timer.expires = jiffies + periodo;
	add_timer(&blink_timer);
	return 0;
}

void cleanup_module(void)
{
	del_timer_sync(&blink_timer);
	module_clean_level(CLEAN_GPIO_DEVICE_CLASS_MAJOR);
	MSG_OK("modulo descarregado");
}

static int device_open(struct inode *inode, struct file *file)
{
	if(Device_Open) return -EBUSY;
	Device_Open++; // Trava acesso ao device
	Device_Counter = 0; // Conta quantos caracteres foram lidos
	try_module_get(THIS_MODULE); // Incrementa o contador de uso do modulo
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--; // Libera acesso ao device
	module_put(THIS_MODULE); // Decrementa o contador de uso do modulo
	return 0;
}

void long_para_string(long int x, char s[])
{
	long int pot10=1;
        int i=0;
        for(pot10=1; pot10<=x; pot10 *= 10){}
        pot10 /= 10;
        for(i=0; pot10>0; i++)
        {
                s[i] = x/pot10 + '0';
                x = x%pot10;
                pot10 /=10;
	}
	s[i] = '\0';
}

static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	long int F = ((100*HZ)/2)/periodo;
	char Fstr[10];
	int i, j;
	long_para_string(F, Fstr);
	for(i=0; Fstr[i]!='\0'; i++);
	Fstr[i+1] = Fstr[i];
	Fstr[i] = Fstr[i-1];
	Fstr[i-1] = Fstr[i-2];
	Fstr[i-2] = '.';
	i++;

	if(Device_Counter>=i)
		return 0;
	for(j=0; (j<length) && (Device_Counter<i); Device_Counter++, j++)
		put_user(Fstr[Device_Counter], buffer+j);
	return j;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	long int x;
	int i, val_len;
	long int casas;
	for(val_len=0; val_len<len; val_len++)
		if((buff[val_len]!='.') && ((buff[val_len]<'0') || (buff[val_len]>'9')))
				break;
	for(i=0; (i<val_len) && (buff[i]!='.'); i++);
	casas = val_len - i - 1;
	for(x=0, i=0; i<val_len; i++)
		if(buff[i]!='.')
			x = (x*10) + (buff[i]-'0');
	periodo = HZ/(2*x);
	while(casas>0)
	{
		periodo *= 10;
		casas--;
	}
	return len;
}
