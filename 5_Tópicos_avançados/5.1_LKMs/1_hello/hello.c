#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
    pr_alert("Hello World :)\n");
    return 0;
}
static void hello_exit(void)
{
    pr_alert("Goodbye World!\n");
}
module_init(hello_init);
module_exit(hello_exit);
