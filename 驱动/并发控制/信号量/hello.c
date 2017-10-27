/*信号量*/
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

struct semaphore sem;
int hello_open(struct inode *inode, struct file *file)//open()
{
	printk("hello_open()\n");
//	down(&sem);//获取信号量。但是它会导致睡眠，且不能被信号中断
	if(down_interruptible(&sem))//这个函数也会导致睡眠，但是可以被信号中断。
	//if(down_trylock(&sem))//这个函数不会导致睡眠，获得信号，返回0，否则返回非0.它可以用于中断上下文。
	{
		return -EAGAIN;
	}
	return 0;
}
int hello_release(struct inode *inode, struct file *file)//close
{
	printk("hello_release()\n");
	up(&sem);
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
	sema_init(&sem,1);
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
