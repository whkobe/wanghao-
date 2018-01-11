#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

dev_t devno;

int minor = 0;
struct cdev cdev;

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
 int major  =250;
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

#if 0 
	ret = alloc_chrdev_region(&devno,minor, 1, "hello");
	if(ret)
	{
		printk(KERN_ERR " alloc_chrdev_region\n");
		return ret;
	}
	major = MAJOR(devno);
	printk("major = %d \n",major);
	/*
	devno = MKDEV(major,minor);
	ret = register_chrdev_region(devno, 1, "hello");
	if(ret)
	{
		printk(KERN_ERR " register_chrdev_region\n");
		return ret;
	}
*/
	
	cdev_init(&cdev, &fops);	
	rc = cdev_add(&cdev , devno, 1);	
	if (rc < 0) 
	{	 
		printk(KERN_ERR " register_chrdev_region\n");
		unregister_chrdev_region(devno, 1);
		return rc;
	}
#endif
	return 0;
}
void hello_exit(void)
{
	printk("hello_exit()\n");
//	cdev_del(  &cdev  );
//	unregister_chrdev_region(devno, 1);
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

/*register_chrdev(unsigned int major, const char * name, const struct file_operations * fops)
    动态 或者 静态申请设备号
    cdev的初始化和注册

参数：
     unsigned int major,    主设备号（静态申请）  可以是0（动态分配）
返回值
    major>0   成功返回0
    major =0  返回主设备号
*/