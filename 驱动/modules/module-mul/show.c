#include <linux/module.h>
#include <linux/kernel.h>

int hello_init(void)
{
	printk("hello_init()\n");
	return 0;
}
void hello_exit()
{
	printk("hello_exit()\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
