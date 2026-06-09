// Modulo do kernel para acender um LED no GPIO4
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/gpio/driver.h>

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err) printk(KERN_ERR "%s: %s %ld\n", DEVICE_NAME, s, PTR_ERR(err))
#define GPIOCHIP_BASE 512
#define BCM_GPIO(n) (GPIOCHIP_BASE + (n))
#define LED1 4

static struct gpio_desc *led;

static int __init gpiomod_init(void)
{
	led = gpio_to_desc(BCM_GPIO(LED1));
	if (!led)
	{
		MSG_BAD("GPIO não encontrado\n", led);
		return -ENODEV;
	}
	gpiod_direction_output(led, 1);
	MSG_OK("modulo carregado");
	return 0;
}

static void __exit gpiomod_exit(void)
{
	if (led)
		gpiod_set_value(led, 0);
	MSG_OK("modulo descarregado");
}

module_init(gpiomod_init);
module_exit(gpiomod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO usando gpiod");
