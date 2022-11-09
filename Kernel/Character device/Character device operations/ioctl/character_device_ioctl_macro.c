#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

#define IO          _IO('a', 0)
#define IOR         _IOR('a', 0, char*)
#define IOW          _IOW('a', 0, char*)
#define IOWR         _IOWR('a', 0, char*)

MODULE_LICENSE("GPL");

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

int dev_open(struct inode *, struct file *);
int dev_close(struct inode *, struct file *);
ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
long dev_ioctl(struct file *, unsigned int cmd, unsigned long arg);

struct struct_arg {
    int number;
    char string_value[30];
} struct_arg_object;

struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write,
	.unlocked_ioctl = dev_ioctl,
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
	printk("read\n");
	return 0;
}

ssize_t dev_write(struct file *filep, const char __user *buf, size_t len, loff_t *offset)
{
	printk("write\n");
	return 0;
}

#define iostruct _IOW('a', 1, struct struct_arg_object*)

long dev_ioctl(struct file *filep, unsigned int cmd, unsigned long arg){
	char usr_arg[30];

	/*
		If setting like this, there will be error:
		case label does not reduce to an integer constant
	*/
	// int iostruct = _IOW('a', 1, sizeof(struct_arg_object));

	copy_from_user(usr_arg, (char*)arg, sizeof(usr_arg));

	switch (cmd){
		case IO:
			printk("_IO(): cmd %d, arg %s\n", cmd, usr_arg);
			break;
		case IOR:
			printk("_IOR(): cmd %d, arg %s\n", cmd, usr_arg);
			break;
		case IOW:
			printk("_IOW(): cmd %d, arg %s\n", cmd, usr_arg);
			break;
		case IOWR:
			printk("_IOWR(): cmd %d, arg %s\n", cmd, usr_arg);
			break;
		case iostruct:
			copy_from_user(&struct_arg_object, (struct struct_arg*)arg, sizeof(struct_arg_object));
			printk("_IOW('a',1): number %d, string value %s\n", struct_arg_object.number, struct_arg_object.string_value);
			break;
		default:
			printk("Default: cmd %d, arg %s\n", cmd, usr_arg);
			break;
	}

	return 0;
}

int device_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev_id, 0, 1, "fops_alloc_chrdev_region");
	if(ret)
	{
		printk("can not register major no\n");
		return ret;
	}
	printk(KERN_INFO "register successfully major now is: %d\n", MAJOR(dev_id));
	character_device = cdev_alloc();
	character_device->owner = THIS_MODULE;
	character_device->ops = &fops;
	character_device->dev = dev_id;

	cdev_add(character_device, dev_id, 1);
	device_class = class_create(THIS_MODULE, DEVICE_CLASS);
	device = device_create(device_class, NULL, dev_id, NULL, DEVICE_NAME);

	return 0;
}

void device_exit(void)
{
	printk("Device remove\n");
	unregister_chrdev_region(dev_id, 0);
	cdev_del(character_device);
	device_destroy(device_class, dev_id);
	class_destroy(device_class);
}

module_init(device_init);
module_exit(device_exit);