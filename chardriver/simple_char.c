#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>



static int hello_init(void)
{
	printk("hello everyone");
	return 0;
}


static void hello_exit(void)
{
	printk("hello everyone");
}


module_init(hello_init);
module_exit(hello_exit);



MODULE_AUTHOR("jyothi");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("hi how are you");


