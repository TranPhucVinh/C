#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h> //for kmalloc()

#define DEVICE_NAME					"miscellaneous_device"

MODULE_LICENSE("GPL");

struct miscdevice *miscellaneous_device;

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
	char responsed_string[] = "Response string from kernel space to user space\n";
	int bytes_response = copy_to_user(buf, responsed_string, sizeof(responsed_string));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(responsed_string);
}

char data[100];
ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	memset(data, 0, sizeof(data));
	copy_from_user(data, buf, len);
	printk("String read from userspace: %s\n", data);
	return sizeof(data);
}

int device_init(void)
{
	miscellaneous_device = (struct miscdevice *)kmalloc(sizeof(struct miscdevice), GFP_KERNEL);
	miscellaneous_device->minor = MISC_DYNAMIC_MINOR;
	miscellaneous_device->name = DEVICE_NAME;
	miscellaneous_device->fops = &fops;

	int ret;
	ret = misc_register(miscellaneous_device);

	if (ret != 0) {
		printk("Unable to register the misc device %s", DEVICE_NAME);
		return ret;
	} else {
		printk("Register misc device successfully with minor number %d", miscellaneous_device->minor);
	}

	return 0;
}

void device_exit(void)
{
	printk("%s is removed\n", DEVICE_NAME);
	misc_deregister(miscellaneous_device); 
}

module_init(device_init);
module_exit(device_exit);