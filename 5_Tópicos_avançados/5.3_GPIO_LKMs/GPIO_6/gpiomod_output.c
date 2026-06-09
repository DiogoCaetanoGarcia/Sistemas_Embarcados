// Modulo do kernel para ligar/desligar LEDs por interrupcoes em botoes
// Utilize um botao para cada LED
// Baseado em https://github.com/wendlers/rpi-kmod-samples/blob/master/modules/kmod-gpio_inpirq/gpiomod_inpirq.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/gpio/driver.h>
#define GPIOCHIP_BASE 512
#define BCM_GPIO(n) (GPIOCHIP_BASE + (n))

#define NLEDS 1
#define NBTNS 1

static const int led_gpios[NLEDS] = {24};
static const int btn_gpios[NBTNS] = {17};

static struct gpio_desc *leds[NLEDS];
static struct gpio_desc *btns[NBTNS];

static int button_irqs[] = {-1};

static irqreturn_t button_isr(int irq, void *data)
{
	for(int i=0; i<ARRAY_SIZE(btns); i++)
	{
		if(irq==button_irqs[i])
		{
			gpiod_set_value(leds[i], !gpiod_get_value(leds[i]));
			while(gpiod_get_value(btns[i])==0);
			mdelay(200);
			return IRQ_HANDLED;
		}
	}
	return IRQ_HANDLED;
}

static void turn_leds_off(int led_start, int led_end)
{
	for(int i = led_start; i <= led_end; i++)
		gpiod_set_value(leds[i], 0);
}

/*
 * Module init function
 */
static int __init gpiomode_init(void)
{
	int ret = 0, i;
	char dev_name[] = "gpiomod#btn  ";

	printk(KERN_INFO "%s\n", __func__);

	for (i = 0; i < NLEDS; i++)
	{
		leds[i] = gpio_to_desc(BCM_GPIO(led_gpios[i]));
		if (!leds[i])
		{
			printk(KERN_ERR	"Unable to get LED GPIO %d\n", led_gpios[i]);
			turn_leds_off(0, i-1);
			return -ENODEV;
		}
		gpiod_direction_output(leds[i], 1);
	}

	for (i = 0; i < NBTNS; i++)
	{
		btns[i] = gpio_to_desc(BCM_GPIO(btn_gpios[i]));
		if (!btns[i])
		{
			printk(KERN_ERR "Unable to get BUTTON GPIO %d\n", btn_gpios[i]);
			turn_leds_off(0, NLEDS-1);
			return -ENODEV;
		}
		gpiod_direction_input(btns[i]);
	}

	printk(KERN_INFO "Current button1 value: %d\n", gpiod_get_value(btns[0]));

	for(i=0; i<NBTNS; i++)
	{
		ret = gpiod_to_irq(btns[i]);
		if(ret < 0)
		{
			printk(KERN_ERR "Unable to map IRQ: %d\n", ret);
			turn_leds_off(0, NLEDS-1);
			return ret;
		}
		button_irqs[i] = ret;
		printk(KERN_INFO "Successfully requested BUTTON1 IRQ # %d\n", button_irqs[i]);
		dev_name[11] = ' ';
		dev_name[12] = ((char)(i%10))+'0';
		if(i>9)
			dev_name[11] = ((char)(i/10))+'0';
		ret = request_irq(button_irqs[i], button_isr, IRQF_TRIGGER_FALLING /* | IRQF_DISABLED */, dev_name, NULL);
		if(ret)
		{
			printk(KERN_ERR "Unable to request IRQ: %d\n", ret);
			turn_leds_off(0, NLEDS-1);
			return ret;
		}
	}
	return 0;
}



/**
 * Module exit function
 */
static void __exit gpiomode_exit(void)
{
	printk(KERN_INFO "%s\n", __func__);
	// free irqs
	for(int i = 0; i < NBTNS; i++)
		free_irq(button_irqs[i], NULL);
	turn_leds_off(0, NLEDS-1);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO!");

module_init(gpiomode_init);
module_exit(gpiomode_exit);
