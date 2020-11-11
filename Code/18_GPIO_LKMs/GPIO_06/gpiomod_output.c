// Modulo do kernel para ligar/desligar LEDs por interrupcoes em botoes
// Utilize um botao para cada LED
// Baseado em https://github.com/wendlers/rpi-kmod-samples/blob/master/modules/kmod-gpio_inpirq/gpiomod_inpirq.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

static struct gpio leds[] = {
		{ 24, GPIOF_OUT_INIT_LOW, "LED 1" },
};

static struct gpio btns[] = {
		{  4, GPIOF_IN, "BUTTON 1" },
};

static int button_irqs[] = {-1};

static irqreturn_t button_isr(int irq, void *data)
{
	int i;
	for(i=0; i<ARRAY_SIZE(btns); i++)
	{
		if(irq==button_irqs[i])
		{
			gpio_set_value(leds[i].gpio, !gpio_get_value(leds[i].gpio));
			while(gpio_get_value(btns[i].gpio)==0);
			mdelay(200);
			return IRQ_HANDLED;
		}
	}
	return IRQ_HANDLED;
}

/*
 * Module init function
 */
static int __init gpiomode_init(void)
{
	int ret = 0, i;
	char dev_name[] = "gpiomod#btn  ";

	printk(KERN_INFO "%s\n", __func__);

	// register LED gpios
	ret = gpio_request_array(leds, ARRAY_SIZE(leds));
	if (ret)
	{
		printk(KERN_ERR "Unable to request GPIOs for LED: %d\n", ret);
		return ret;
	}

	// register BUTTON gpios
	ret = gpio_request_array(btns, ARRAY_SIZE(btns));
	if (ret)
	{
		printk(KERN_ERR "Unable to request GPIOs for BUTTON: %d\n", ret);
		gpio_free_array(leds, ARRAY_SIZE(leds));
		return ret;
	}

	printk(KERN_INFO "Current button1 value: %d\n", gpio_get_value(btns[0].gpio));

	for(i=0; i<ARRAY_SIZE(btns); i++)
	{
		ret = gpio_to_irq(btns[i].gpio);
		if(ret < 0)
		{
			printk(KERN_ERR "Unable to map IRQ: %d\n", ret);
			gpio_free_array(btns, ARRAY_SIZE(btns));
			gpio_free_array(leds, ARRAY_SIZE(leds));
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
			gpio_free_array(btns, ARRAY_SIZE(btns));
			gpio_free_array(leds, ARRAY_SIZE(leds));
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
	int i;

	printk(KERN_INFO "%s\n", __func__);

	// free irqs
	for(i = 0; i < ARRAY_SIZE(btns); i++)
		free_irq(button_irqs[i], NULL);

	// turn all LEDs off
	for(i = 0; i < ARRAY_SIZE(leds); i++)
		gpio_set_value(leds[i].gpio, 0);

	// unregister
	gpio_free_array(leds, ARRAY_SIZE(leds));
	gpio_free_array(btns, ARRAY_SIZE(btns));
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO!");

module_init(gpiomode_init);
module_exit(gpiomode_exit);
