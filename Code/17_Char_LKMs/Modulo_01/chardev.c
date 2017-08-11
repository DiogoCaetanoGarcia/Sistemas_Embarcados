// Codigo para criar um dispositivo de leitura
// que sempre retorna um caracter '1'

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola char driver!");

#define DEVICE_NAME "chardev"

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

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

int init_module(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if(Major < 0)
	{
		printk(KERN_ALERT "Erro ao registrar char device: %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "Major number assinalado: %d.\n", Major);
	printk(KERN_INFO "Para comunicar como driver, crie um arquivo dev:\n");
	printk(KERN_INFO "   mknod /dev/%s c %d %d\n", DEVICE_NAME, Major, Minor);
	printk(KERN_INFO "Tente varios minors. Tente usar cat e echo com o arquivo dev.\n");
	printk(KERN_INFO "Remova o arquivo dev e o modulo quando terminar.\n");
	return 0;
}

void cleanup_module(void)
{
	unregister_chrdev(Major, DEVICE_NAME); // Liberar o device
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
	if(Device_Counter>0) return 0; // Se ja foi lido mais de um byte, end of file
	put_user('1', buffer);         // Caso contrario, retorne um carcater 1
	Device_Counter++;
	return 1;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Operacao nao suportada.\n");
	return -EINVAL;
}
