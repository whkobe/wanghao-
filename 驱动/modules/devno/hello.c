#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

dev_t devno;
int major = 250;
int minor = 0;

int hello_init(void)
{
	int ret;
	
	printk("hello_init()\n");
	devno = MKDEV(major,minor);
	ret = register_chrdev_region(devno, 1, "hello");//注册设备号，cat /proc/devices 查看设备号
	if(ret)
	{
		printk(KERN_ERR " register_chrdev_region\n");
		return ret;
	}
	
	return 0;
}
void hello_exit()
{
	printk("hello_exit()\n");
	unregister_chrdev_region(devno, 1);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
