// Codigo para criar um dispositivo de escrita em GPIO

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola LCD Device Driver!");

#define DEVICE_NAME "lcd_device_driver"
#define CLASS_NAME  "lcd_device_driver_class"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %ld\n", DEVICE_NAME, s, err_val)

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
char Send_Nibble(char nibble, char nibble_type);
char Send_Byte(char byte, char byte_type);
void Clear_LCD(void);
void Config_LCD(void);
void Send_String(char *str);
void jiffies_delay(unsigned int n);

#define DADO 1
#define COMANDO 0
#define EN 0
#define RS 1
#define D4 2
#define D5 3
#define D6 4
#define D7 5
#define LCD_LINE_LEN 16

static struct gpio lcd_pins[] = {
		{  4, GPIOF_OUT_INIT_LOW, "EN" },
		{ 27, GPIOF_OUT_INIT_LOW, "RS" },
		{ 22, GPIOF_OUT_INIT_LOW, "D4" },
		{ 23, GPIOF_OUT_INIT_LOW, "D5" },
		{ 24, GPIOF_OUT_INIT_LOW, "D6" },
		{ 25, GPIOF_OUT_INIT_LOW, "D7" },
};
static int Major;     // Major number para o device driver
static int Minor = 0; // Minor number definido por mim
static int Device_Open = 0;    // Device aberto? Usado para prevenir acesso multiplo ao device
static int Device_Counter = 0; // Posicao do arquivo para leitura e escrita
static struct class*  lcd_device_driver_Class  = NULL; ///< The device-driver class struct pointer
static struct device* lcd_device_driver_Device = NULL; ///< The device-driver device struct pointer
static char lcd_text[LCD_LINE_LEN];

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
	int i;
	if(level<1)
	{
		// Apagar LEDs
		for(i = 0; i < ARRAY_SIZE(lcd_pins); i++)
			gpio_set_value(lcd_pins[i].gpio, 0);
		// Liberar GPIOs dos LEDs
		gpio_free_array(lcd_pins, ARRAY_SIZE(lcd_pins));
	}
	if(level<2) // Remove o dispositivo
		device_destroy(lcd_device_driver_Class, MKDEV(Major, 0));
	if(level<3) // Desfaz o registro da classe de dispositivo e remove a classe de dispositivo
	{
		class_unregister(lcd_device_driver_Class);
		class_destroy(lcd_device_driver_Class);
	}
	if(level<4) // Desfaz o registro do major number
		unregister_chrdev(Major, DEVICE_NAME);
}

int init_module(void)
{
	int ret, i;
	// Obter major number dinamicamente
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if(Major < 0)
	{
		MSG_BAD("erro ao registrar GPIO device", (long int)Major);
		return Major;
	}
	MSG_OK("registrado corretamente");
	// Registrar a classe do dispositivo
	lcd_device_driver_Class = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(lcd_device_driver_Class)) // Se houve erro no registro
	{
		module_clean_level(CLEAN_MAJOR);
		MSG_BAD("falhou em registrar a classe do dispositivo", PTR_ERR(lcd_device_driver_Class));
		return PTR_ERR(lcd_device_driver_Class); // Correct way to return an error on a pointer
	}
	MSG_OK("classe do dispositivo registrada corretamente");

	// Registrar o device driver
	lcd_device_driver_Device = device_create(lcd_device_driver_Class, NULL, MKDEV(Major, Minor), NULL, DEVICE_NAME);
	if(IS_ERR(lcd_device_driver_Device)) // Se houve erro no registro
	{
		module_clean_level(CLEAN_DEVICE_MAJOR);
		MSG_BAD("falhou em criar o device driver", PTR_ERR(lcd_device_driver_Device));
		return PTR_ERR(lcd_device_driver_Device);
	}
	MSG_OK("dispositivo criado corretamente");

	// Registrar GPIOs para LEDs, ligar LEDs
	ret = gpio_request_array(lcd_pins, ARRAY_SIZE(lcd_pins));
	if(ret)
		MSG_BAD("não conseguiu acesso ao GPIO", (long int)ret);
	else
		MSG_OK("modulo carregado");

	for(i=0; i<LCD_LINE_LEN; i++)
		lcd_text[i] = '\0';
	lcd_text[0] = 'O';
	lcd_text[1] = 'l';
	lcd_text[2] = 'a';
	lcd_text[3] = ' ';
	lcd_text[4] = 'L';
	lcd_text[5] = 'C';
	lcd_text[6] = 'D';
	Config_LCD();
	Send_String(lcd_text);

	return ret;
}

void cleanup_module(void)
{
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

static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	int i;
	// End of file
	if(Device_Counter>=LCD_LINE_LEN)
		return 0;
	for(i=0; (i<length)&&(Device_Counter<LCD_LINE_LEN); i++, Device_Counter++)
		put_user(lcd_text[Device_Counter], buffer+i);
	return i;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	int i;
	char local_buff[LCD_LINE_LEN+1]={'\0'};
	Clear_LCD();
	Device_Counter = 0;
	for(i=0; (i<len)&&(Device_Counter<LCD_LINE_LEN); i++, Device_Counter++)
		local_buff[i] = lcd_text[Device_Counter] = buff[i];
	local_buff[i] = lcd_text[Device_Counter] = '\0';
	Send_String(local_buff);
	return i;
}


char Send_Nibble(char nibble, char nibble_type)
{
	if((nibble_type!=DADO)&&(nibble_type!=COMANDO))
		return -1;
	gpio_set_value(lcd_pins[EN].gpio, 1);
	gpio_set_value(lcd_pins[RS].gpio, nibble_type);
	gpio_set_value(lcd_pins[D4].gpio, nibble&1);
	gpio_set_value(lcd_pins[D5].gpio, (nibble>>1)&1);
	gpio_set_value(lcd_pins[D6].gpio, (nibble>>2)&1);
	gpio_set_value(lcd_pins[D7].gpio, (nibble>>3)&1);
	gpio_set_value(lcd_pins[EN].gpio, 0);
	jiffies_delay(1);
	return 0;
}

char Send_Byte(char byte, char byte_type)
{
	if(Send_Nibble(byte>>4, byte_type)==-1)
		return -1;
	Send_Nibble(byte & 0xF, byte_type);
	return 0;
}

void Clear_LCD(void)
{
	Send_Byte(0x01, COMANDO);
	jiffies_delay(2);
	Send_Byte(0x02, COMANDO);
	jiffies_delay(2);
}

void Config_LCD(void)
{
	jiffies_delay(1);
	Send_Nibble(0x2, COMANDO);
	Send_Byte(0x20, COMANDO);
	Send_Byte(0x14, COMANDO);
	Send_Byte(0x0C, COMANDO);
	Send_Byte(0x06, COMANDO);
	Clear_LCD();
}

void Send_String(char *str)
{
	int i = 0;
	while(str[i]!='\0')
	{
		Send_Byte(str[i], DADO);
		i++;
	}
}

void jiffies_delay(unsigned int n)
{
	unsigned long t_end = jiffies + n*HZ/100;
	while(jiffies<t_end);
}
