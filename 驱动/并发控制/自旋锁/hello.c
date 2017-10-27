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

spinlock_t  lock;//定义自旋锁
int flage= 1;

int hello_open(struct inode *inode, struct file *file)//open()
{
	printk("hello_open()\n");

	spin_lock(&lock);//获得自旋锁
	if(flage!=1)
	{
		spin_unlock(&lock);//释放
		return -EBUSY;
	}
	flage=0;
	
	return 0;
}
int hello_release(struct inode *inode, struct file *file)//close
{
	printk("hello_release()\n");
	spin_unlock(&lock);
	flage=1;
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
	spin_lock_init(&lock);//初始化自旋锁
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
//我们打开两个终端，运行test.c，只有当第一个test运行结束后，释放锁，第二个test才能运行
