#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SREEKANTH");
MODULE_DESCRIPTION("SAMPLE_PROGRAM");
MODULE_VERSION("1.0");

static int hello_init(void)
{
printk("hello world\n");
return 0;
}

static void hello_exit(void)
{
printk("gud bye\n");
}

module_init(hello_init);
module_exit(hello_exit);

