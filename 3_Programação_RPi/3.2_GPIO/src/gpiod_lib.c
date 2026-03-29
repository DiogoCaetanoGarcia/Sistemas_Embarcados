#include "../inc/gpiod_lib.h"

void gpio_write(int offset, int value) {
	struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");

	struct gpiod_line_settings *settings = gpiod_line_settings_new();
	gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
	gpiod_line_settings_set_output_value(settings, value);

	struct gpiod_line_config *cfg = gpiod_line_config_new();
	unsigned int offsets[] = {offset};
	gpiod_line_config_add_line_settings(cfg, offsets, 1, settings);

	struct gpiod_request_config *req = gpiod_request_config_new();
	struct gpiod_line_request *r = gpiod_chip_request_lines(chip, req, cfg);

	gpiod_line_request_release(r);
	gpiod_chip_close(chip);
}
