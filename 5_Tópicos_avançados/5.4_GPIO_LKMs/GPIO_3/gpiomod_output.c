// Modulo do kernel para piscar um LED no GPIO4
// Baseado em https://github.com/wendlers/rpi-kmod-samples/tree/master/modules/kmod-gpio_outptimer
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define NEWER_KERNEL_TIMER

#define DEVICE_NAME "gpiomod_output"
#define MSG_OK(s) printk(KERN_INFO "%s: %s\n", DEVICE_NAME, s)
#define MSG_BAD(s, err_val) printk(KERN_ERR "%s: %s %d\n", DEVICE_NAME, s, err_val)
#define LED1 4
#define LED1_NAME "LED1"
#define LED_FREQ_2 (HZ/5)
static struct timer_list blink_timer;
static unsigned long t;

#ifdef NEWER_KERNEL_TIMER
static void blink_timer_func(struct timer_list* data)
#else
static void blink_timer_func(unsigned long data)
#endif
{
	t += LED_FREQ_2;
	// Agendar proxima execucao
	blink_timer.expires = t;//jiffies + LED_FREQ_2;
	add_timer(&blink_timer);
	gpio_set_value(LED1, !gpio_get_value(LED1));
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
	// Comeca o timer
#ifdef NEWER_KERNEL_TIMER
	__init_timer(&blink_timer, blink_timer_func, 0);
#else
	init_timer(&blink_timer);
#endif
	// Ao final da contagem do timer, a funcao blink_timer_func() deve ser executada
	blink_timer.function = blink_timer_func;
	// jiffies eh uma variavel global que indica a quantidade de periodos do clock desde que ocorreu o boot do sistema
	// HZ representa a quantidade de ciclos para contabilizar um segundo
	// LED_FREQ_2 = 200ms
	blink_timer.expires = t = jiffies + LED_FREQ_2;
	add_timer(&blink_timer);
	return ret;
}

void cleanup_module(void)
{
	// Desativa o timer, se ele estiver rodando
	del_timer_sync(&blink_timer);
	gpio_set_value(LED1, 0);
	gpio_free(LED1);
	MSG_OK("modulo descarregado");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO!");
