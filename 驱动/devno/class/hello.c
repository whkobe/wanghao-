#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
dev_t devno;
 int major  =250;
int minor = 0;
struct cdev cdev;

struct class *cls;
struct device *mydev;

int hello_open(struct inode *inode, struct file *file)//open()
{
	printk("hello_open()\n");
	return 0;
}
int hello_release(struct inode *inode, struct file *file)//close
{
	printk("hello_release()\n");
	return 0;
}
 struct file_operations  fops={
	.owner		= THIS_MODULE,
	.open		= hello_open,
	.release	       = hello_release,
 };
int hello_init(void)
{
	int ret;

	printk("hello_init()\n");
	ret = register_chrdev(major,"hello", &fops);
	if(ret<0)
	{
		printk(KERN_ERR " alloc_chrdev_region\n");
		return major;
	}
	devno = MKDEV(major,minor);
	
	cls = class_create(THIS_MODULE, "mycls");
	if (IS_ERR(cls)) {
		unregister_chrdev(major, "hello");
		return PTR_ERR(cls);
	}
	mydev = device_create(cls, NULL, devno, NULL, "mydev");//“mydev”设备节点，设备名
	if (IS_ERR(mydev)) {
		unregister_chrdev(major, "hello");
		class_destroy(cls);
		return PTR_ERR(mydev);
	}
	return 0;
}
void hello_exit(void)
{
	device_destroy(cls, devno);
	class_destroy(cls);
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
