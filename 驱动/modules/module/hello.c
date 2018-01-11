#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>



unsigned int nf_hookfn(const struct nf_hook_ops *ops,
			       struct sk_buff *skb,
			       const struct net_device *in,
			       const struct net_device *out,
			       int (*okfn)(struct sk_buff *))
{

	
}


struct nf_hook_ops filter={
	.hook = myfilter,
	.owner = THIS_MODULE,
	.hooknum = NF_INET_PRE_ROUTING
	.priority = NF_IP_PRI_FIRST
	.pf = PF_INET
	}


int hello_init(void)
{	
	nf_register_hook(&filter)


	
	return 0;
}
void hello_exit()
{
	
	nf_unregister_hook(&filter)
	
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
