#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

MODULE_LICENSE("GPL");

struct task_struct *userspace_process; //Use this to communicate with the userspace process

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

int dev_open(struct inode *, struct file *);
int dev_close(struct inode *, struct file *);
ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
long dev_ioctl(struct file *, unsigned int cmd, unsigned long arg);

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

long dev_ioctl(struct file *filep, unsigned int cmd, unsigned long arg){
	int userspace_argument;
	copy_from_user(&userspace_argument, (int*)arg, sizeof(userspace_argument));
	printk("cmd %d, arg %d, userspace_argument %d\n", cmd, arg, userspace_argument);

    userspace_process = get_current();

    /*
        This will get the PID of the userspace process that sends ioctl() system
        call to it.
    */
    printk("PID %d\n", userspace_process->pid);
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
