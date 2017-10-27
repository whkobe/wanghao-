#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

void	hello_release(struct device *dev)
{
	printk("device:hello_release()\n");
}
struct platform_device pdev={
	.name = "duang",//这个名字和platform——driver下的名字一样
	.id = -1,
	.dev.release = hello_release,
};

int hello_init(void)
{
	printk("hello_init()\n");
	return platform_device_register(&pdev);
}
void hello_exit(void)
{
	printk("hello_exit()\n");
	platform_device_unregister(&pdev);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
//通过名字来匹配驱动