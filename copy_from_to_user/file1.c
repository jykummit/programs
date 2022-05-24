#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/version.h>
#include<linux/slab.h>
#include<linux/uaccess.h>


#define DEVICE_NAME "copy_to_from_user"
static int major;
unsigned char *ptr;

int device_open(struct inode *pinode, struct file *fp){
	printk("Hello world from %s\n",__func__);
	return 0;
}
ssize_t device_read(struct file *fp,char __user *buff, size_t length, loff_t *off){
	printk("Hello world from %s\n",__func__);

	if(copy_to_user(buff,ptr,length)){
		printk("copying to user failed \n");
	}
	else{
		printk("copying to user is success using %s\n",buff);
	}
	kfree(ptr);
	return 0;
}

ssize_t device_write(struct file *fp,const char __user *buff, size_t length, loff_t *off){
	printk("Hello world from %s\n",__func__);

	ptr = kzalloc(length,GFP_KERNEL);

	if(ptr == NULL){
		printk("memory allocation Failed \n");
	}
	else{
		printk("memory allocation success \n");

		if (copy_from_user(ptr,buff,length)){
			printk("copying from user failed \n");
			return -1;
		}
		else{
			printk("copying from user is success using %s\n",buff);
		}

		printk("%s\n",buff);
	}
	
	return length;
}

int device_release(struct inode *pinode, struct file *fp){
	printk("Hello world from %s\n",__func__);
	return 0;
}

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int hello_init(void){
	major = register_chrdev(0,DEVICE_NAME,&fops);
	if(major < 0)
	{
		printk("registration failed %d\n",major);
	}
	printk("%d\n",major);
	printk(KERN_ALERT "Hello world from %s\n",__func__);
	return 0;
}

static void hello_exit(void){
	unregister_chrdev(major,DEVICE_NAME);

	printk(KERN_ALERT "Hello World from %s\n",__func__);
}


module_init(hello_init);
module_exit(hello_exit);


MODULE_AUTHOR("Sreekanth");
MODULE_DESCRIPTION("Example_Character_Drivers");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
