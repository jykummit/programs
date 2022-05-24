#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/unistd.h>

int major;
int device_open(struct inode *pinode , struct file *ifile){
	printk(KERN_ALERT "called function %s\n",__func__);
	return 0;
}

ssize_t device_read (struct  file *ifile, char __user *buf , size_t length, loff_t *offset){
	printk(KERN_ALERT "called function %s\n",__func__);
	if(get_from_user:wq

	return 0;
}

ssize_t device_write(struct file *ifile, const char __user *buf , size_t length, loff_t *offset){
	printk(KERN_ALERT "called function %s\n",__func__);
	return length;
}

int device_release(struct inode *pinode,struct file *ifile){
	printk(KERN_ALERT "called function %s\n",__func__ );
	return 0;
}


struct file_operations fops ={
	.open=device_open,
	.write=device_write,
	.read=device_read,
	.release=device_release
};



static int hello_init(void)
{
	printk(KERN_ALERT "called function %s\n",__func__);
	major = register_chrdev(0,"Example_driver",&fops);
	printk("%d",major);
	return 0;
}


static void hello_exit(void)
{
	printk(KERN_ALERT "called function %s\n",__func__);
	unregister_chrdev(major,"Example_driver");
}


module_init(hello_init);
module_exit(hello_exit);


MODULE_AUTHOR("jyothi");
MODULE_DESCRIPTION("hello everyone");
MODULE_LICENSE("GPL");
