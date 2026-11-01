#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

static int __init hello_init(void)
{
	pr_info("kernel_lab: hello module loaded\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("kernel_lab: hello module unloaded\n");
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rootkit-io");
MODULE_DESCRIPTION("First kernel module: initalization and cleanup");



