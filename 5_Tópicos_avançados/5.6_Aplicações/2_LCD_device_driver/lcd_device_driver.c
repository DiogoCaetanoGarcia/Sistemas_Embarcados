#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> /* Updated from asm/uaccess.h */
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/gpio/consumer.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola LCD Device Driver (Platform/DTS)");

#define DEVICE_NAME "lcd_device_driver"
#define CLASS_NAME  "lcd_device_driver_class"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %ld\n", DEVICE_NAME, s, err_val)

#define DADO 1
#define COMANDO 0
#define LCD_LINE_LEN 16

/* Context structure for our device */
struct lcd_dev {
	struct gpio_desc *en;
	struct gpio_desc *rs;
	struct gpio_desc *d4;
	struct gpio_desc *d5;
	struct gpio_desc *d6;
	struct gpio_desc *d7;
	int major;
	struct class *lcd_class;
	struct device *lcd_device;
	int is_open;
	int counter;
	char text[LCD_LINE_LEN + 1];
};

static struct lcd_dev *lcd_data;

/* Forward declarations */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/* --- Hardware Abstraction --- */

static char Send_Nibble(char nibble, char nibble_type)
{
	if ((nibble_type != DADO) && (nibble_type != COMANDO))
		return -1;
	gpiod_set_value(lcd_data->en, 1);
	gpiod_set_value(lcd_data->rs, nibble_type);
	gpiod_set_value(lcd_data->d4, nibble & 1);
	gpiod_set_value(lcd_data->d5, (nibble >> 1) & 1);
	gpiod_set_value(lcd_data->d6, (nibble >> 2) & 1);
	gpiod_set_value(lcd_data->d7, (nibble >> 3) & 1);
	gpiod_set_value(lcd_data->en, 0);
	msleep(10);
	return 0;
}

static char Send_Byte(char byte, char byte_type)
{
	if (Send_Nibble(byte >> 4, byte_type) == -1)
		return -1;
	Send_Nibble(byte & 0xF, byte_type);
	return 0;
}

static void Clear_LCD(void)
{
	Send_Byte(0x01, COMANDO);
	msleep(20);
	Send_Byte(0x02, COMANDO);
	msleep(20);
}

static void Config_LCD(void)
{
	msleep(10);
	Send_Nibble(0x3, COMANDO);
	Send_Nibble(0x3, COMANDO);
	Send_Nibble(0x3, COMANDO);
	Send_Nibble(0x2, COMANDO);
	Send_Byte(0x20, COMANDO);
	Send_Byte(0x14, COMANDO);
	Send_Byte(0x0C, COMANDO);
	Send_Byte(0x06, COMANDO);
	Clear_LCD();
}

static void Send_String(char *str)
{
	int i = 0;
	while (str[i] != '\0' && i < LCD_LINE_LEN) {
		Send_Byte(str[i], DADO);
		i++;
	}
}

/* --- File Operations --- */

static int device_open(struct inode *inode, struct file *file)
{
	if (lcd_data->is_open) return -EBUSY;
	lcd_data->is_open++;
	lcd_data->counter = 0;
	try_module_get(THIS_MODULE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	lcd_data->is_open--;
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
	int i;
	if (lcd_data->counter >= LCD_LINE_LEN)
		return 0;
	for (i = 0; (i < length) && (lcd_data->counter < LCD_LINE_LEN) && (lcd_data->text[lcd_data->counter] != '\0'); i++, lcd_data->counter++) {
		put_user(lcd_data->text[lcd_data->counter], buffer + i);
	}
	return i;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	int i;
	char local_buff[LCD_LINE_LEN + 1] = {'\0'};
	Clear_LCD();
	lcd_data->counter = 0;
	for (i = 0; (i < len) && (lcd_data->counter < LCD_LINE_LEN); i++, lcd_data->counter++) {
		lcd_data->text[lcd_data->counter] = buff[i];
		local_buff[i] = buff[i];
	}
	lcd_data->text[lcd_data->counter] = '\0';
	local_buff[i] = '\0';
	Send_String(local_buff);
	return i;
}

/* --- Platform Driver Callbacks --- */

static int lcd_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	lcd_data = devm_kzalloc(dev, sizeof(struct lcd_dev), GFP_KERNEL);
	if (!lcd_data) return -ENOMEM;

	/* 1. Get GPIOs from Device Tree */
	lcd_data->en = devm_gpiod_get(dev, "en", GPIOD_OUT_LOW);
	lcd_data->rs = devm_gpiod_get(dev, "rs", GPIOD_OUT_LOW);
	lcd_data->d4 = devm_gpiod_get(dev, "d4", GPIOD_OUT_LOW);
	lcd_data->d5 = devm_gpiod_get(dev, "d5", GPIOD_OUT_LOW);
	lcd_data->d6 = devm_gpiod_get(dev, "d6", GPIOD_OUT_LOW);
	lcd_data->d7 = devm_gpiod_get(dev, "d7", GPIOD_OUT_LOW);

	if (IS_ERR(lcd_data->en) || IS_ERR(lcd_data->rs) || IS_ERR(lcd_data->d4) || 
		IS_ERR(lcd_data->d5) || IS_ERR(lcd_data->d6) || IS_ERR(lcd_data->d7)) {
		MSG_BAD("Failed to get GPIOs from DTS", PTR_ERR(lcd_data->en));
		return -ENODEV;
	}

	/* 2. Setup Character Device */
	lcd_data->major = register_chrdev(0, DEVICE_NAME, &fops);
	if (lcd_data->major < 0) {
		MSG_BAD("Erro ao registrar GPIO device", (long int)lcd_data->major);
		return lcd_data->major;
	}

	lcd_data->lcd_class = class_create(CLASS_NAME);
	if (IS_ERR(lcd_data->lcd_class)) {
		unregister_chrdev(lcd_data->major, DEVICE_NAME);
		return PTR_ERR(lcd_data->lcd_class);
	}

	lcd_data->lcd_device = device_create(lcd_data->lcd_class, NULL, MKDEV(lcd_data->major, 0), NULL, DEVICE_NAME);
	if (IS_ERR(lcd_data->lcd_device)) {
		class_destroy(lcd_data->lcd_class);
		unregister_chrdev(lcd_data->major, DEVICE_NAME);
		return PTR_ERR(lcd_data->lcd_device);
	}

	/* 3. Initialize Hardware */
	strcpy(lcd_data->text, "Ola LCD");
	Config_LCD();
	Send_String(lcd_data->text);

	MSG_OK("DTS LCD Module Loaded");
	return 0;
}

static void lcd_remove(struct platform_device *pdev)
{
	/* Turn off the screen before exiting */
	Clear_LCD();

	device_destroy(lcd_data->lcd_class, MKDEV(lcd_data->major, 0));
	class_unregister(lcd_data->lcd_class);
	class_destroy(lcd_data->lcd_class);
	unregister_chrdev(lcd_data->major, DEVICE_NAME);

	MSG_OK("DTS LCD Module Unloaded");
}

/* --- Device Tree Match Table --- */
static const struct of_device_id lcd_of_match[] = {
	{ .compatible = "se,lcd-gpio", },
	{ },
};
MODULE_DEVICE_TABLE(of, lcd_of_match);

static struct platform_driver lcd_driver = {
	.probe = lcd_probe,
	.remove = lcd_remove,
	.driver = {
		.name = "lcd_device_driver",
		.of_match_table = lcd_of_match,
	},
};

module_platform_driver(lcd_driver);
