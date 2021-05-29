// Modulo do kernel para acender LEDs no GPIOs 4, 24 e 25
// Baseado em https://github.com/wendlers/rpi-kmod-samples/tree/master/modules/kmod-gpio_output
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %d\n", DEVICE_NAME, s, err_val)

static struct gpio leds[] = {
		{  4, GPIOF_OUT_INIT_HIGH, "LED 1" },
		{ 25, GPIOF_OUT_INIT_HIGH, "LED 2" },
		{ 24, GPIOF_OUT_INIT_HIGH, "LED 3" },
};

int init_module(void)
{
	// Registrar GPIOs para LEDs, ligar LEDs
	int ret = gpio_request_array(leds, ARRAY_SIZE(leds));

	if(ret)
		MSG_BAD("não conseguiu acesso ao GPIO", ret);
	else
		MSG_OK("modulo carregado");
	return ret;
}

void cleanup_module(void)
{
	int i;
	// Apagar LEDs
	for(i = 0; i < ARRAY_SIZE(leds); i++)
	{
		gpio_set_value(leds[i].gpio, 0);
	}
	// Liberar GPIOs dos LEDs
	gpio_free_array(leds, ARRAY_SIZE(leds));
	MSG_OK("modulo descarregado");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO!");
