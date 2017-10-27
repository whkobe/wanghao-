//通过ioctl来实现流水灯。封装命令。
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>

void fs4412_led_off(int ledno);

dev_t devno;
 int major  =250;
int minor = 0;
struct cdev cdev;

struct class *cls;
struct device *mydev;


#define GPX2CON  0x11000C40    
#define GPX2DAT   0x11000C44
#define GPX1CON   0x11000C20   
#define GPX1DAT     0x11000C24
#define GPF3CON    0x114001E0  
#define GPF3DAT      0x114001E4

void *pgpx2con;
void *pgpx2dat;
void *pgpx1con;
void *pgpx1dat;
void *pgpf3con;
void *pgpf3dat;


void led_ioremap(void)
{
	pgpx2con = ioremap( GPX2CON,4);
	pgpx2dat = ioremap( GPX2DAT,4);
	pgpx1con = ioremap( GPX1CON,4);
	pgpx1dat = ioremap( GPX1DAT,4);
	pgpf3con = ioremap( GPF3CON,4);
	pgpf3dat = ioremap( GPF3DAT ,4);	
}

void led_iounmap(void)
{
	iounmap(pgpx2con);
	iounmap(pgpx2dat);
	iounmap(pgpx1con);
	iounmap(pgpx1dat);
	iounmap(pgpf3con);
	iounmap(pgpf3dat );
}
void fs4412_led_init(void)
{
	writel((readl(pgpx2con) &( ~(0xf<<28))) | (0x1<<28),pgpx2con);
	writel((readl(pgpx1con) &( ~(0xf<<0))) | (0x1<<0),pgpx1con);
	writel((readl(pgpf3con) &( ~(0xff<<16))) | (0x11<<16),pgpf3con);	
}
void fs4412_led_on(int ledno)
{
	switch(ledno)
	{
		case 1:
			writel(readl(pgpx2dat) | (0x1<<7),pgpx2dat);
			break;
		case 2:
			writel(readl(pgpx1dat) | (0x1<<0),pgpx1dat);
			break;
		case 3:
			writel(readl(pgpf3dat) | (0x1<<4),pgpf3dat);
			break;
		case 4:
			writel(readl(pgpf3dat) | (0x1<<5),pgpf3dat);
			break;
		default:
			fs4412_led_off(1);
			fs4412_led_off(2);
			fs4412_led_off(3);
			fs4412_led_off(4);
			break;
	}
}
void fs4412_led_off(int ledno)
{
	switch(ledno)
	{
		case 1:
			writel(readl(pgpx2dat) & (~(0x1<<7)),pgpx2dat);
			break;
		case 2:
			writel(readl(pgpx1dat)&(~ (0x1<<0)),pgpx1dat);
			break;
		case 3:
			writel(readl(pgpf3dat) &(~ (0x1<<4)),pgpf3dat);
			break;
		case 4:
			writel(readl(pgpf3dat)&(~ (0x1<<5)),pgpf3dat);
			break;
	}
}
int hello_open(struct inode *inode, struct file *file)//open()
{
	printk("hello_open()\n");

	return 0;
}
int hello_release(struct inode *inode, struct file *file)//close
{
	printk("hello_release()\n");
	fs4412_led_off(1);
	fs4412_led_off(2);
	fs4412_led_off(3);
	fs4412_led_off(4);
	return 0;
}

//封装ioctl的命令。
#define FS4412_LED_MAGIC   'k'//设备类型，为一个幻数
#define  FS4412_LED_ON      _IOW (FS4412_LED_MAGIC,0,  int )//内核提供的宏用于生成命令
#define  FS4412_LED_OFF     _IOW (FS4412_LED_MAGIC,1,  int)
//这里封装了两个命令，开灯和关灯。在我的测试代码里，也要封装这两个命令
long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case FS4412_LED_ON:
			printk("FS4412_LED_ON arg = %d \n",arg);
			fs4412_led_on(arg);
			break;

		case FS4412_LED_OFF:
			printk("FS4412_LED_OFF arg = %d \n",arg);
			fs4412_led_off(arg);
			break;
	}
	return 0;
}
 struct file_operations  fops={
	.owner		= THIS_MODULE,
	.open		= hello_open,
	.release	       = hello_release,
	.unlocked_ioctl = hello_ioctl,
 };
int hello_init(void)
{
	int ret,rc;

	printk("hello_init()\n");
	ret = register_chrdev(major,"hello", &fops);	
	devno = MKDEV(major,minor);	
	cls = class_create(THIS_MODULE, "mycls");
	mydev = device_create(cls, NULL, devno, NULL, "hello");
	led_ioremap();
	fs4412_led_init();
	return 0;
}
void hello_exit(void)
{
	led_iounmap();
	device_destroy(cls, devno);
	class_destroy(cls);
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
