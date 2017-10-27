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

static atomic_t v = ATOMIC_INIT(1);

int hello_open(struct inode *inode, struct file *file)//open()
{
	printk("hello_open()\n");

	if(!atomic_dec_and_test(&v))//自减并且测试其是否为0，为0返回true，否则返回false
	{
		atomic_inc(&v);
		return -EBUSY;
	}
	return 0;
}
int hello_release(struct inode *inode, struct file *file)//close
{
	printk("hello_release()\n");
	atomic_inc(&v);
	return 0;
}
 struct file_operations  fops={
	.owner		= THIS_MODULE,
	.open		= hello_open,
	.release	       = hello_release,
 };
int hello_init(void)
{
	int ret,rc;

	printk("hello_init()\n");
	ret = register_chrdev(major,"hello", &fops);	
	devno = MKDEV(major,minor);	
	cls = class_create(THIS_MODULE, "mycls");
	mydev = device_create(cls, NULL, devno, NULL, "hello");
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
