// Modulo do kernel para acender LEDs nos GPIOs 4, 24 e 25
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/gpio/driver.h>

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err) printk(KERN_ERR "%s: %s %ld\n", DEVICE_NAME, s, PTR_ERR(err))
#define GPIOCHIP_BASE 512
#define BCM_GPIO(n) (GPIOCHIP_BASE + (n))

#define NLEDS 3

static const int gpio_numbers[NLEDS] = {4, 25, 24};
static struct gpio_desc *leds[NLEDS];

static int __init gpiomod_init(void)
{
	int i;

	for (i = 0; i < NLEDS; i++)
	{
		leds[i] = gpio_to_desc(BCM_GPIO(gpio_numbers[i]));
		if (!leds[i])
		{
			printk(KERN_ERR "%s: GPIO%d nao encontrado\n",
			       DEVICE_NAME, gpio_numbers[i]);
			while (--i >= 0)
				gpiod_set_value(leds[i], 0);
			return -ENODEV;
		}

		gpiod_direction_output(leds[i], 1);
	}
	MSG_OK("modulo carregado");
	return 0;
}

static void __exit gpiomod_exit(void)
{
	int i;
	for (i = 0; i < NLEDS; i++)
	{
		if (leds[i])
			gpiod_set_value(leds[i], 0);
	}
	MSG_OK("modulo descarregado");
}

module_init(gpiomod_init);
module_exit(gpiomod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO usando gpiod");
