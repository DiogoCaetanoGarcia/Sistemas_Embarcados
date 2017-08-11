// Modulo do kernel para piscar um LED no GPIO4
// Baseado em https://github.com/wendlers/rpi-kmod-samples/tree/master/modules/kmod-gpio_outptimer
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %d\n", DEVICE_NAME, s, err_val)
#define LED1 4
#define LED1_NAME "LED1"
#define LED_FREQ_2 (HZ/5)
static struct timer_list blink_timer;

static void blink_timer_func(unsigned long data)
{
	gpio_set_value(LED1, data);
	// Agendar proxima execucao
	blink_timer.data = !data; // Inverte o valor do LED
	blink_timer.expires = jiffies + LED_FREQ_2;
	add_timer(&blink_timer);
}

int init_module(void)
{
	// Registrar GPIO para LED, ligar LED
	int ret = gpio_request_one(LED1, GPIOF_OUT_INIT_LOW, LED1_NAME);
	if(ret)
	{
		MSG_BAD("não conseguiu acesso ao GPIO", ret);
		return ret;
	}
	MSG_OK("modulo carregado");
	// Comeca o timer, adiciona funcao do timer
	init_timer(&blink_timer);
	blink_timer.function = blink_timer_func;
	blink_timer.data = 1L;	// Comeca com o LED ligado
	blink_timer.expires = jiffies + LED_FREQ_2;
	add_timer(&blink_timer);
	return ret;
}

void cleanup_module(void)
{
	gpio_set_value(LED1, 0);
	gpio_free(LED1);
	// Desativa o timer, se ele estiver rodando
	del_timer_sync(&blink_timer);
	MSG_OK("modulo descarregado");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO!");
