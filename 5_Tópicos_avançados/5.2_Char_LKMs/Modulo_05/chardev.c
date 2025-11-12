// Codigo para criar um dispositivo de leitura
// que fornece numeros primos menores do que 1000.
// Começa em '2' e termina em '997',
// voltando ao '2' em seguida.

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola char driver!");

#define DEVICE_NAME "chardev"
#define CLASS_NAME  "chardev_class"

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
int eh_primo(int n);

static int Major;     // Major number para o device driver
static int Minor = 0; // Minor number definido por mim
static int Device_Open = 0;    // Device aberto? Usado para prevenir acesso multiplo ao device
static int Device_Counter = 0; // Contador para saber quantos caracteres foram lidos
static int primo = 2;      // Variável que guarda o último primo escrito
static struct class*  chardev_Class  = NULL; ///< The device-driver class struct pointer
static struct device* chardev_Device = NULL; ///< The device-driver device struct pointer

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

int init_module(void)
{
	// Obter major number dinamicamente
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if(Major < 0)
	{
		printk(KERN_ALERT "Erro ao registrar char device: %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "Chardev: registrado corretamente com major number %d\n", Major);
	// Registrar a classe do dispositivo
	chardev_Class = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(chardev_Class)) // Se houve erro no registro
	{
		unregister_chrdev(Major, DEVICE_NAME);
		printk(KERN_ALERT "Falhou em registrar a classe do dispositivo\n");
		return PTR_ERR(chardev_Class); // Correct way to return an error on a pointer
	}
	printk(KERN_INFO "Chardev: classe do dispositivo registrada corretamente\n");

	// Registrar o device driver
	chardev_Device = device_create(chardev_Class, NULL, MKDEV(Major, Minor), NULL, DEVICE_NAME);
	if(IS_ERR(chardev_Device)) // Se houve erro no registro
	{
		class_destroy(chardev_Class);
		unregister_chrdev(Major, DEVICE_NAME);
		printk(KERN_ALERT "Falhou em criar o device driver\n");
		return PTR_ERR(chardev_Device);
	}
	printk(KERN_INFO "Chardev: dispositivo criado corretamente\n");
	return 0;
}

void cleanup_module(void)
{
	device_destroy(chardev_Class, MKDEV(Major, 0)); // Remove o dispositivo
	class_unregister(chardev_Class); // Desfaz o registro da classe de dispositivo
	class_destroy(chardev_Class); // Remove a classe de dispositivo
	unregister_chrdev(Major, DEVICE_NAME); // Desfaz o registro do major number
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
	if(Device_Counter>1) return 0;
	if(length>1)
	{
		if(primo<10)
		{
			put_user(' ', buffer);
			put_user(' ', buffer+1);
			put_user(primo+'0', buffer+2);
		}
		else if(primo<100)
		{
			put_user(' ', buffer);
			put_user((primo/10) + '0', buffer+1);
			put_user((primo%10) + '0', buffer+2);
		}
		else
		{
			put_user((primo/100)+'0', buffer);
			put_user(((primo%100)/10) + '0', buffer+1);
			put_user((primo%10) + '0', buffer+2);
		}
		Device_Counter+=3;
		if(primo == 2) primo = 3;
		else
		{
			do
			{
				primo += 2;
			}while(eh_primo(primo)==0);
			if(primo>999) primo=2;
		}
		return 3;
	}
	/*else
	{
		if(Device_Counter==0)
		{
			if(last_val<10)
				put_user(' ', buffer);
			else
				put_user((last_val/10) + '0', buffer);
			Device_Counter++;
		}
		else
		{
			put_user((last_val%10)+'0', buffer);
			Device_Counter++;
			last_val = (last_val==99) ? (0) : (last_val+1);
		}
		return 1;
	}*/
	return 0;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Operacao nao suportada.\n");
	return -EINVAL;
	//last_char = buff[len-1];
	//return 1;
}

int eh_primo(int n)
{
	int i;
	for(i=2; i<n/2; i++)
	{
		if((n%i)==0)
		{
			return 0;
		}
	}
	return 1;
}




