#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>








static int cdp_init(void){

	return 0;
}



static void cdp_cleanup(void){
	
	int err;
	dev_t dev_number;
	dev_major = MAJOR(dev_number);
	err = alloc_chrdev_region(&dev_number,0,1,DEVICE_NAME);
	cdp_class = class_create(THIS_MODULE,DEVICE_NAME);
	cdev_init(&cdp_dev,&fops);
	cdp.owner = THIS_MODULE;
	cdev_add(&cdp_dev.cdev,dev_major,1);
	device_create(cdp_class,NULL,dev_major,NULL,DEVICE_NAME);
	printk("Module succesfully registered\n");
	return 0;
}






module_init(cdp_init);
module_exit(cdp_cleanup);



MODULE_AUTHOR("Self");
MODULE_DESCRIPTION("A Simple Character Driver");
MODULE_LICENSE("GPL");
