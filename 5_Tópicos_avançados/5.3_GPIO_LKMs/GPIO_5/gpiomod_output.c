// Codigo para criar um dispositivo de escrita em GPIO

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put_user */
#include <linux/init.h>  // Macros used to mark up functions e.g. __init __exit
#include <linux/device.h> // Header to support the kernel Driver Model
#include <linux/gpio.h>

#define NEWER_KERNEL_TIMER

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
static long int meio_periodo=HZ/5;

#ifdef NEWER_KERNEL_TIMER
static void blink_timer_func(struct timer_list* data)
#else
static void blink_timer_func(unsigned long data)
#endif
{
	// Agendar proxima execucao
	blink_timer.expires = jiffies + meio_periodo;
	add_timer(&blink_timer);
	gpio_set_value(LED1, !gpio_get_value(LED1));
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
#define CLEAN_CLASS_MAJOR             2
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
		module_clean_level(CLEAN_CLASS_MAJOR);
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
// Comeca o timer
#ifdef NEWER_KERNEL_TIMER
	__init_timer(&blink_timer, blink_timer_func, 0);
#else
	init_timer(&blink_timer);
#endif
	blink_timer.function = blink_timer_func;
	blink_timer.expires = jiffies + meio_periodo;
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

int arredondar_divisao(int dividendo, int divisor)
{
	return (dividendo + (divisor/2))/divisor;
}

static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			char *buffer,	/* buffer to fill with data */
			size_t length,	/* length of the buffer     */
			loff_t * offset)
{
	int F;
	char Fstr[10];
	int tam_str, j;
	// Obter frequencia_atual*100 
	F = arredondar_divisao(100*HZ, 2*meio_periodo);
	// Escrever frequência atual em string
	// com duas casas decimais 
	sprintf(Fstr, "%d.%02d\n", F/100, F%100);
	// Obter tamanho da string da frequência
	tam_str = strlen(Fstr);
	// Escrever string da frequência no buffer
	// indicado pelo usuário
	if(Device_Counter>=tam_str)
		return 0;
	for(j=0; (j<length) && (Device_Counter<tam_str); Device_Counter++, j++)
		put_user(Fstr[Device_Counter], buffer+j);
	// Retornar quantidade de caracteres escritos
	return j;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	int parte_inteira=0, casas_decimais=0, cnt, n_casas, freq_sem_casas_decimais;
	// Obter parte inteira e casas decimais da frequencia
	// indicada pelo usuário. 'cnt' indica quantos valores
	// foram detectados
	cnt = sscanf(buff, "%d.%d", &parte_inteira, &casas_decimais);
	// Precisamos de 1 ou 2 valores positivos detectados
	if((cnt<1)||(cnt>2)||(parte_inteira<0)||(casas_decimais<0))
	{
		MSG_BAD("Invalid frequency value!", -1l);
		return 0;
	}
	// Calcular quantidade de casas decimais.
	// P.ex., se o usuário indicou 2.50, temos
	// parte_inteira=2 e casas_decimais=50,
	// e obtemos n_casas=100
	for(n_casas=1; n_casas<=casas_decimais; n_casas*=10);
	// Calcular frequência sem casas decimais.
	// P.ex., se o usuário indicou 2.50, temos
	// parte_inteira=2, casas_decimais=50, n_casas=100
	// e obtemos freq_sem_casas_decimais=2*100+50=250
	freq_sem_casas_decimais = parte_inteira*n_casas+casas_decimais;
	// Não podemos ter uma frequência nula
	if(freq_sem_casas_decimais==0)
	{
		MSG_BAD("Invalid frequency value!", -1l);
		return 0;
	}
	// Calcular meio período
	meio_periodo = arredondar_divisao(HZ*n_casas, 2*freq_sem_casas_decimais);
	return len;
}
