#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/uaccess.h>


dev_t devno;
int major  =250;
int minor = 0;
struct cdev cdev;

struct class *cls;
struct device *mydev;

wait_queue_head_t rq;
char kbuf[]="kernel\n";
int havedata=0;


ssize_t hello_read (struct file *file, char __user *buf, size_t size, loff_t *pos)
{
	if(havedata==0)
	{
		//if(file->f_flags &= O_NONBLOCK)
		//if(file->f_flags== O_NONBLOCK)//这样写错误。永远不可能出非阻塞。因为flags是我们在open的时候的设置的，其实就是位操作
		if((file->f_flags) & O_NONBLOCK)//如果在open的时候使用了O_NONLOCK，就不会阻塞
		
		{
			return -EAGAIN;
		}
		wait_event_interruptible(rq,havedata==1);//可以被信号打断
	}
	if(size>strlen(kbuf))
	{
		size=strlen(kbuf);
	}
	if(copy_to_user(buf,kbuf,size))
	{
		return -EFAULT;
	}
	havedata=0;
	return size;

}
ssize_t hello_write (struct file *file, const char __user *buf, size_t size, loff_t *pos)
{
	if(size>sizeof(kbuf))
	{
		size=sizeof(kbuf);
	}
	if(copy_from_user(kbuf,buf,size))
	{
		return -EFAULT;
	}
	kbuf[size]='\0';
	wake_up_interruptible(&rq);
	havedata=1;
	return size;
}

int hello_open(struct inode *inode, struct file *file)
{
	printk("hello_open()\n");


	return 0;
}
int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release()\n");



	return 0;
}
struct file_operations  fops={
	.owner		= THIS_MODULE,
	.open		= hello_open,
	.release	= hello_release,
	.write      = hello_write,
	.read       = hello_read,
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
	mydev = device_create(cls, NULL, devno, NULL, "hello");
	if (IS_ERR(mydev)) {
		unregister_chrdev(major, "hello");
		class_destroy(cls);
		return PTR_ERR(mydev);
	}
	init_waitqueue_head(&rq);
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
