#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>

static int hello_init(void){
printk("hai team \n");
return 0;
}

static void hello_exit(void){
printk("hru");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("jyothi");
MODULE_DESCRIPTION("this is kernel module programming");
MODULE_LICENSE("GPL");
