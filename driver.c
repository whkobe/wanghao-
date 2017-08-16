#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/sched.h>
int major = 250;

wait_queue_head_t wq;
int havedata = 0;
int key;
struct platform_device *key_pdev;

irqreturn_t key_handler(int irqno, void *dev)
{
//	printk("====irqno %d=======\n",irqno);

	if(irqno == key_pdev->resource[0].start)
	{
		key = 1;
	}
	if(irqno == key_pdev->resource[1].start)
	{
		key = 2;
	}
	havedata = 1;
	wake_up_interruptible(&wq);
	return IRQ_HANDLED;
}

int key_open(struct inode *inode, struct file *file)
{
	return 0 ;
}
int key_release(struct inode *inode, struct file *file)
{
	return 0 ;
}

ssize_t fs4412key_read(struct file *file, char __user *buf, size_t size, loff_t *pos)
{
	wait_event_interruptible(wq, havedata==1);

	if(size!=4)
	{
		return -EFAULT;
	}
	if(copy_to_user(buf, &key, size))
	{
		return -EFAULT;
	}
	havedata = 0;
	return size;
}
struct file_operations  fops={
	.open = key_open,
	.release = key_release,
	.read = fs4412key_read,
};

int hello_probe(struct platform_device *pdev)
{
	int ret;
	key_pdev = pdev;
	printk("match ok\n");
	ret = request_irq(pdev->resource[0].start,key_handler, pdev->resource[0].flags, "key1", NULL);
	ret = request_irq(pdev->resource[1].start,key_handler, pdev->resource[1].flags, "key2", NULL);

	register_chrdev(major, "key", &fops);
	init_waitqueue_head(&wq);
	return 0;
}
int hello_remove(struct platform_device *pdev)
{
	printk("hello_remove\n");

	unregister_chrdev(major, "key");
	free_irq(key_pdev->resource[0].start, NULL);
	free_irq(key_pdev->resource[1].start, NULL);
	return 0;
}
struct of_device_id 	key_tbl[]={
	{.compatible = "fs4412,key"},
};
struct platform_driver pdrv={
	.probe = hello_probe,
	.remove = hello_remove,
	.driver.name  ="duang",
	.driver.of_match_table = key_tbl,
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
