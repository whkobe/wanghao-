#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/poll.h>

dev_t devno;
 int major  =250;
int minor = 0;
struct cdev cdev;

struct class *cls;
struct device *mydev;

wait_queue_head_t rq;
wait_queue_head_t wq;
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
char kbuf[64]="kernel";
int havedata=0;//0 nodata   1  have data

ssize_t hello_read (struct file *file, char __user *buf, size_t size, loff_t *pos)
{

	wait_event_interruptible(rq, havedata==1);
	if(size>strlen(kbuf))
	{
		size = strlen(kbuf);
	}

	if(copy_to_user(buf, kbuf, size))
	{
		return -EFAULT;
	}
	havedata = 0;
	wake_up_interruptible(&wq);
	return size;
	
}
ssize_t hello_write(struct file *file, const char __user *buf, size_t size, loff_t *pos)
{
	wait_event_interruptible(wq, havedata==0);
	if(size > sizeof(kbuf))
	{
		size = sizeof(kbuf);
	}

	if(copy_from_user( kbuf,buf, size))
	{
		return -EFAULT;
	}
	kbuf[size]='\0';
	havedata = 1;
	wake_up_interruptible(&rq);
	
	return size;
}
unsigned int hello_poll(struct file *file, struct poll_table_struct *tbl)
{
	int mask=0;
	
	poll_wait(file, &rq, tbl);
	poll_wait(file, &wq, tbl);
	
	if(havedata == 1)
	{
		mask|=POLLIN;
	}
	if(havedata ==0)
	{
		mask|=POLLOUT;
	}
	return mask;
}
 struct file_operations  fops={
	.owner		= THIS_MODULE,
	.open		= hello_open,
	.release	       = hello_release,
	.read             = hello_read,
	.write           = hello_write,
	.poll              = hello_poll,
 };
int hello_init(void)
{
	int ret,rc;

	printk("hello_init()\n");
	ret = register_chrdev(major,"hello", &fops);	
	devno = MKDEV(major,minor);	
	cls = class_create(THIS_MODULE, "mycls");
	mydev = device_create(cls, NULL, devno, NULL, "hello");
	init_waitqueue_head(&rq);
	init_waitqueue_head(&wq);	
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
