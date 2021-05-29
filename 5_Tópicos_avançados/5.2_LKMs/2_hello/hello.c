#include <linux/module.h>
#include <linux/kernel.h>

int hello_init(void)
{
    pr_alert("Hello World :)\n");
    return 0;
}
void hello_exit(void)
{
    pr_alert("Goodbye World!\n");
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Olá Linux Kernel Module!");
