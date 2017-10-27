#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/io.h>
#include <asm/uaccess.h>

dev_t devno;
int major  =250;
int minor = 0;
struct cdev cdev;

struct class *cls;
struct device *mydev;


#define BEEP_MAGIC 'k'
#define BEEP_ON _IO(BEEP_MAGIC,0)
#define BEEP_OFF _IO(BEEP_MAGIC,1)
#define BEEP_FRE _IO(BEEP_MAGIC,2)

#define TCFG0  0x0000   
#define TCFG1  0x0004     
#define TCON  0x0008     
#define TCNTB0 0x000C    
#define TCMPB0 0x0010  

void *pgpd0con ;
void *timer0_base;


#define PWM_IN_FRE 100000
void fs4412_beep_fre(int fre)
{
	writel(PWM_IN_FRE/fre,timer0_base+TCNTB0);
	writel(PWM_IN_FRE/(fre*2),timer0_base+TCMPB0);	
}

void fs4412_beep_on(void)
{
	writel((readl(timer0_base+TCON) &(~(0xf<<0))) | (0x1<<3|0x1<<0),timer0_base+TCON);
}
void fs4412_beep_off(void)
{
	writel((readl(timer0_base+TCON) &(~(0xf<<0))) | 0x0<<0,timer0_base+TCON);
}

void fs4412_beep_init(void)
{
	writel((readl(pgpd0con)	&(~(0xf<<0)))  | 0x2<<0  ,pgpd0con);
	writel((readl(timer0_base+TCFG0) &(~(0xff<<0))) | 0xff,timer0_base+TCFG0);
	writel((readl(timer0_base+TCFG1) &(~(0xf<<0))) | 0x1,timer0_base+TCFG1);
	writel(500,timer0_base+TCNTB0);
	writel(250,timer0_base+TCMPB0);
	writel((readl(timer0_base+TCON) &(~(0xf<<0))) | 0x1<<1,timer0_base+TCON);
}

void beep_iounmap(void)
{
	iounmap(pgpd0con);
	iounmap(timer0_base);
}

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
long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case BEEP_ON:
			fs4412_beep_on();
			break;
		case BEEP_OFF:
			fs4412_beep_off();
			break;
		case BEEP_FRE:
			fs4412_beep_fre(arg);
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
int hello_probe(struct platform_device *pdev)
{
	int ret,rc;
	printk("match ok\n");

	pgpd0con = ioremap(pdev->resource[0].start,pdev->resource[0].end-pdev->resource[0].start+1);
	timer0_base = ioremap(pdev->resource[1].start,pdev->resource[1].end-pdev->resource[1].start+1);

	ret = register_chrdev(major,"hello", &fops);	
	devno = MKDEV(major,minor);	
	cls = class_create(THIS_MODULE, "mycls");
	mydev = device_create(cls, NULL, devno, NULL, "hello");
	fs4412_beep_init();
	return 0;
}
int hello_remove(struct platform_device *pdev)
{
	printk("hello_remove\n");
	beep_iounmap();
	device_destroy(cls, devno);
	class_destroy(cls);
	unregister_chrdev(major, "hello");
	return 0;
}
struct of_device_id	beep_tbl[]={
	{
		.compatible ="fs4412,beep"//驱动使用compatible属性，来匹配设备树。最终还是将设备树转换成device下的资源
	},
};
struct platform_driver pdrv={
	.probe = hello_probe,
	.remove = hello_remove,
	.driver.name  ="duang",
	.driver.of_match_table = beep_tbl,
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

/*设备树的编写
fs4412-beep{
		compatible="fs4412,beep";
		reg=<0x114000A0 0x4 0x139D0000 0x14>;最终解析成两个资源
	};
	*/