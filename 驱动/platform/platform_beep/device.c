#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

void	hello_release(struct device *dev)
{
	printk("device:hello_release()\n");
}

struct resource beep_res[]={
	[0]={
		.start = 0x114000A0  ,
		.end  = 0x114000A0 +0x3,
		.flags = IORESOURCE_MEM,
	},

	[1]={
		.start = 0x139D0000  ,
		.end  = 0x139D0000 +0x13,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device pdev={
	.name = "duang",
	.id = -1,
	.dev.release = hello_release,
	.resource = beep_res,//硬件资源
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
