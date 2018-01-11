#include <linux/module.h>
#include <linux/kernel.h>

extern void show(void);

int hello_init(void)
{
	printk("hello_init()\n");
	show();
	return 0;
}
void hello_exit(void)
{
	printk("hello_exit()\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
