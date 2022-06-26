#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#define MAJOR_NUMBER 90
#define MINOR_NUMBER 0
#define DEVICE_NAME					"fops_character_device"

MODULE_LICENSE("GPL");

int dev_open(struct inode *, struct file *);
int dev_close(struct inode *, struct file *);
ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);

struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write,
};

int dev_open(struct inode *inodep, struct file *filep)
{
	printk("open\n");
	return 0;
}

int dev_close(struct inode *inodep, struct file *filep)
{
	printk("close\n");
	return 0;
}

ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	printk("Handle read operation from userspace, e.g cat /dev/fops_character_device\n");
	return 0;
}

ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	printk("Handle write operation from userspace, e.g echo \"Data\" > /dev/character_device_name\n");
	return 0;
}

/*
	register_chrdev() this will just simply register a character device to /proc/devices
	this character device will not appear on /dev
	to make it available on /dev, use mknod
*/
int device_init(void)
{
	int ret;

	ret = register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &fops);

	if (!ret){
		printk("Register device number major %d, minor %d\n", MAJOR_NUMBER, MINOR_NUMBER);
		return ret;
	} else printk("Can't register character device\n");

	return 0;
}

void device_exit(void)
{
	unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
	printk("Character device unregister\n");
}

module_init(device_init);
module_exit(device_exit);