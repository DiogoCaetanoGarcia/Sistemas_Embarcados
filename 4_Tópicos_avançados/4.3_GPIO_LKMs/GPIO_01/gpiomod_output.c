// Modulo do kernel para acender um LED no GPIO4
// Baseado em https://github.com/wendlers/rpi-kmod-samples/tree/master/modules/kmod-gpio_output
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %d\n", DEVICE_NAME, s, err_val)
#define LED1 4
#define LED1_NAME "LED1"

int init_module(void)
{
	// Registrar GPIO para LED, ligar LED
	int ret = gpio_request_one(LED1, GPIOF_OUT_INIT_HIGH, LED1_NAME);
	if(ret)
		MSG_BAD("não conseguiu acesso ao GPIO", ret);
	else
		MSG_OK("modulo carregado");
	return ret;
}

void cleanup_module(void)
{
	gpio_set_value(LED1, 0);
	gpio_free(LED1);
	MSG_OK("modulo descarregado");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO!");
