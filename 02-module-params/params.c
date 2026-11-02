#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

static int count = 1;

module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of greetings, from 1 to 5");

static int __init params_init(void)
{
	int i;

	if (count < 1 || count > 5) {
		pr_err("kernel_lab: count must be 1 to 5; got %d\n", count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++)
		pr_info("kernel_lab: getting %d of %d\n", i + 1, count);

	return 0;
}

static void __exit params_exit(void)
{
	pr_info("kernel_lab: params module unloaded\n");
}

module_init(params_init);
module_exit(params_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rootkit-io");
MODULE_DESCRIPTION("Module parameters with bounded input validation");

