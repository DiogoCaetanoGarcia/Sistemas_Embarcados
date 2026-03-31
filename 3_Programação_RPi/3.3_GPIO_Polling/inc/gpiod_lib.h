#pragma once
#include <gpiod.h>
#include <stdlib.h>
#include <pthread.h>

typedef enum {
	GPIO_INPUT,
	GPIO_OUTPUT
} gpio_mode_t;

typedef enum {
	GPIO_BIAS_NONE,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN
} gpio_bias_t;

typedef enum {
	GPIO_EDGE_NONE,
	GPIO_EDGE_RISING,
	GPIO_EDGE_FALLING,
	GPIO_EDGE_BOTH
} gpio_edge_t;

typedef void (*gpio_callback_t)(unsigned int pin, int value);

typedef struct {
	struct gpiod_chip *chip;
	struct gpiod_line_request *req;

	unsigned int *pins;
	int count;

	gpio_callback_t cb;
	int running;
	pthread_t thread;
} gpio_t;

gpio_t* gpio_open(unsigned int *pins, int count, gpio_mode_t mode, gpio_bias_t bias, gpio_edge_t edge);
void gpio_close(gpio_t *g);
void gpio_write(gpio_t *g, int index, int value);
int gpio_read(gpio_t *g, int index);

void gpio_set_callback(gpio_t *g, gpio_callback_t cb);
int gpio_poll(gpio_t *g, int timeout_ms, unsigned int *triggered, int max_events);
void gpio_flush_events(gpio_t *g);
//static void* gpio_thread(void *arg);
