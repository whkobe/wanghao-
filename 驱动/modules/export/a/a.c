#include <linux/module.h>
#include <linux/kernel.h>

static int num=10;

static void show(void)
{
	
	printk("a show()%d\n",num);	
}

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
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(show);
module_init(hello_init);
module_exit(hello_exit);
