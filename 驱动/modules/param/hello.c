#include <linux/module.h>
#include <linux/kernel.h>

int howmany = 10;
char *whom="kernel\n";

int hello_init(void)
{
	printk("hello_init()\n");
	printk("howmany=%d  whom=%s \n",howmany,whom);
	return 0;
}
void hello_exit()
{
	printk("hello_exit()\n");
	printk("howmany=%d  whom=%s \n",howmany,whom);
	return;
}

module_param(howmany, int, 0600);
module_param(whom, charp, 0600);
//只能root 有修改权限


MODULE_LICENSE("GPL");

module_init(hello_init);
module_exit(hello_exit);
//sudo insmod hello.ko howmany=15 whom="aaaaaaaaaaaaaa"