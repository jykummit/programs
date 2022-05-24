#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/fs.h>

#define DEVICE_NAME "char_dev"
static int major;

int device_open(struct inode *pinode, struct file *fp){
	printk("Hello from %s\n",__func__);
	return 0;
}

ssize_t device_read(struct file *fp, char __user *buff, size_t length, loff_t *off){
	printk("Hello from %s\n",__func__);
	return 10;
}
ssize_t device_write(struct file *fp, const char __user *buff, size_t length, loff_t *off){
	printk("Hello from %s\n",__func__);
	printk("%ld\n",length);
	printk("%s\n",buff);
	return length;
}
int device_release(struct inode *pinode, struct file *fp){
	printk("Hello from %s\n",__func__);
	return 0;
}

struct file_operations fops = {
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};


static int hello_init(void){
	major = register_chrdev(0,DEVICE_NAME,&fops);
	if(major < 0){
		printk("Device failed to register: %d\n",major);
	}
	printk("%d\n",major);
	printk(KERN_ALERT "Hello World! from %s\n",__func__);
	return 0;
}

static void hello_exit(void){
	unregister_chrdev(major,DEVICE_NAME);
	printk(KERN_ALERT "Good Bye! %s\n",__func__);
}


module_init(hello_init);
module_exit(hello_exit);


MODULE_AUTHOR("Sreekanth");
MODULE_DESCRIPTION("Example_Character_Drivers");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

