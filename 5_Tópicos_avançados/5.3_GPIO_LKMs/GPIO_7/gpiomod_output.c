// Modulo do kernel para acender um LED via Device Tree
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>

#define DEVICE_NAME "gpiomod_output"

static struct gpio_desc *led;

static int gpiomod_probe(struct platform_device *pdev)
{
	led = devm_gpiod_get(&pdev->dev, "my-led", GPIOD_OUT_HIGH);
	if (IS_ERR(led))
	{
		dev_err(&pdev->dev, "Falha ao obter GPIO\n");
		return PTR_ERR(led);
	}
	dev_info(&pdev->dev, "Modulo carregado\n");
	return 0;
}

static void gpiomod_remove(struct platform_device *pdev)
{
	gpiod_set_value(led, 0);
	dev_info(&pdev->dev, "Modulo descarregado\n");
}

static const struct of_device_id gpiomod_of_match[] = {
	{ .compatible = "soe,gpiomod-output" },
	{ }
};

MODULE_DEVICE_TABLE(of, gpiomod_of_match);

static struct platform_driver gpiomod_driver = {
	.probe  = gpiomod_probe,
	.remove = gpiomod_remove,
	.driver = {
		.name = DEVICE_NAME,
		.of_match_table = gpiomod_of_match,
	},
};

module_platform_driver(gpiomod_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola GPIO usando Device Tree");
