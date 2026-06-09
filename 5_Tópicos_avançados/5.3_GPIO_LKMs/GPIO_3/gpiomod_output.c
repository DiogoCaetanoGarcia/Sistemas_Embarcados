// Modulo do kernel para piscar um LED no GPIO4
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/gpio/driver.h>
#include <linux/timer.h>

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define GPIOCHIP_BASE 512
#define BCM_GPIO(n) (GPIOCHIP_BASE + (n))
#define LED1 4
#define LED_FREQ_2 (HZ/5)

static struct gpio_desc *led;
static struct timer_list blink_timer;
static unsigned long t;

static void blink_timer_func(struct timer_list *data)
{
	t += LED_FREQ_2;
	/* agenda próxima execução */
	blink_timer.expires = t;
	add_timer(&blink_timer);
	gpiod_set_value(led, !gpiod_get_value(led));
}

static int __init gpiomod_init(void)
{
	led = gpio_to_desc(BCM_GPIO(LED1));

	if (!led)
	{
		printk(KERN_ERR "%s: GPIO%d nao encontrado\n",
		       DEVICE_NAME, LED1);
		return -ENODEV;
	}
	gpiod_direction_output(led, 0);
	MSG_OK("modulo carregado");

	timer_setup(&blink_timer, blink_timer_func, 0);
	t = jiffies + LED_FREQ_2;
	blink_timer.expires = t;
	add_timer(&blink_timer);
	return 0;
}

static void __exit gpiomod_exit(void)
{
	timer_delete_sync(&blink_timer);
	if (led)
		gpiod_set_value(led, 0);
	MSG_OK("modulo descarregado");
}

module_init(gpiomod_init);
module_exit(gpiomod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO usando gpiod");
