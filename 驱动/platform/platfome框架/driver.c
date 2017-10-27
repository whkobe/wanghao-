#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

int hello_probe(struct platform_device *pdev)
{
	printk("match ok\n");
	return 0;
}
int hello_remove(struct platform_device *pdev)
{
	printk("hello_remove\n");
	return 0;
}
	
struct platform_driver pdrv={
	.probe = hello_probe,
	.remove = hello_remove,
	.driver.name  ="duang",
};
int hello_init(void)
{
	printk("hello_init()\n");
	return platform_driver_register(&pdrv);
}
void hello_exit(void)
{
	printk("hello_exit()\n");
	platform_driver_unregister(&pdrv);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
