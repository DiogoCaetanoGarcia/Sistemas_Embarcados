#include "../inc/gpiod_lib.h"

static void* gpio_thread(void *arg)
{
	gpio_t *g = (gpio_t*)arg;

	while (g->running) {
		int ret = gpiod_line_request_wait_edge_events(g->req, -1);
		if (ret > 0) {
			struct gpiod_edge_event_buffer *buf =
				gpiod_edge_event_buffer_new(1);

			int n = gpiod_line_request_read_edge_events(g->req, buf, 1);
			if (n > 0 && g->cb) {
				int val = gpiod_line_request_get_value(g->req, g->pin);
				g->cb(val);
			}

			gpiod_edge_event_buffer_free(buf);
		}
	}
	return NULL;
}

gpio_t* gpio_open(int pin, gpio_mode_t mode, gpio_bias_t bias, gpio_edge_t edge)
{
	gpio_t *g = calloc(1, sizeof(gpio_t));
	if (!g) return NULL;

	g->chip = gpiod_chip_open("/dev/gpiochip0");
	if (!g->chip) return NULL;

	struct gpiod_line_settings *s = gpiod_line_settings_new();

	gpiod_line_settings_set_direction(
		s,
		mode == GPIO_OUTPUT ?
		GPIOD_LINE_DIRECTION_OUTPUT :
		GPIOD_LINE_DIRECTION_INPUT
	);

	if (bias == GPIO_PULL_UP)
		gpiod_line_settings_set_bias(s, GPIOD_LINE_BIAS_PULL_UP);
	else if (bias == GPIO_PULL_DOWN)
		gpiod_line_settings_set_bias(s, GPIOD_LINE_BIAS_PULL_DOWN);

	if (edge == GPIO_EDGE_RISING)
		gpiod_line_settings_set_edge_detection(s, GPIOD_LINE_EDGE_RISING);
	else if (edge == GPIO_EDGE_FALLING)
		gpiod_line_settings_set_edge_detection(s, GPIOD_LINE_EDGE_FALLING);
	else if (edge == GPIO_EDGE_BOTH)
		gpiod_line_settings_set_edge_detection(s, GPIOD_LINE_EDGE_BOTH);

	struct gpiod_line_config *cfg = gpiod_line_config_new();
	unsigned int offsets[] = {pin};
	gpiod_line_config_add_line_settings(cfg, offsets, 1, s);

	struct gpiod_request_config *rcfg = gpiod_request_config_new();

	g->req = gpiod_chip_request_lines(g->chip, rcfg, cfg);
	if (!g->req) return NULL;

	g->pin = pin;
	return g;
}

void gpio_set_callback(gpio_t *g, gpio_callback_t cb)
{
	g->cb = cb;
	g->running = 1;
	pthread_create(&g->thread, NULL, gpio_thread, g);
}

void gpio_write(gpio_t *g, int value)
{
	gpiod_line_request_set_value(g->req, g->pin, value);
}

int gpio_read(gpio_t *g)
{
	return gpiod_line_request_get_value(g->req, g->pin);
}

int gpio_poll(gpio_t *g, int timeout_ms)
{
    return gpiod_line_request_wait_edge_events(g->req, timeout_ms);
}

void gpio_close(gpio_t *g)
{
	if (!g) return;

	if (g->running) {
		g->running = 0;
		pthread_join(g->thread, NULL);
	}

	if (g->req) gpiod_line_request_release(g->req);
	if (g->chip) gpiod_chip_close(g->chip);

	free(g);
}
