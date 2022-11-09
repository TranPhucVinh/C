#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

#define TOTAL_MINOR                1
#define BASE_MINOR				   0

MODULE_LICENSE("GPL");

int dev_open(struct inode *, struct file *);
int dev_close(struct inode *, struct file *);
ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);

struct chr_dev_info {
	struct cdev *character_device;
	struct class *device_class;
	struct device *device;
	dev_t dev_id;
} dev_info;

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
	printk("read\n");
	return 0;
}

char data[100];
ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	memset(data, 0, sizeof(data));
	copy_from_user(data, buf, len);
	printk("write data: %s\n", data);
	return sizeof(data);
}

/**
 * create_character_device - Create a character device
 * @dev_name:
 * @dev_class:
 * @total_minor:
 * @base_minor:
 * @dev_info:
 * @fops:
 */
int create_character_device(const char* dev_name, const char* dev_class, int total_minor, int base_minor, struct chr_dev_info *dev_info, struct file_operations *fops){
	int ret;

	ret = alloc_chrdev_region(&(dev_info->dev_id), base_minor, total_minor, "fops_alloc_chrdev_region");
	if(ret)
	{
		printk("can not register major no\n");
		return ret;
	}
	printk(KERN_INFO "register successfully major now is: %d\n", MAJOR(dev_info->dev_id));
	dev_info->character_device = cdev_alloc();
	dev_info->character_device->owner = THIS_MODULE;
	dev_info->character_device->ops = fops;
	dev_info->character_device->dev = dev_info->dev_id;

	cdev_add(dev_info->character_device, dev_info->dev_id, 1);
	dev_info->device_class = class_create(THIS_MODULE, dev_class);
	dev_info->device = device_create(dev_info->device_class, NULL, dev_info->dev_id, NULL, dev_name);

	return 0;
}

void destroy_character_device(struct chr_dev_info *dev_info, int total_minor){
	unregister_chrdev_region(dev_info->dev_id, total_minor); 
	cdev_del(dev_info->character_device);
	device_destroy(dev_info->device_class, dev_info->dev_id);
	class_destroy(dev_info->device_class);
}

int device_init(void)
{
	if (create_character_device(DEVICE_NAME, DEVICE_CLASS, TOTAL_MINOR, BASE_MINOR, &dev_info, &fops)){
		printk("Unable to create character device %s\n", DEVICE_NAME);
		return -1;
	}
	return 0;
}

void device_exit(void)
{
	printk("Device %s remove\n", DEVICE_NAME);
	destroy_character_device(&dev_info, TOTAL_MINOR);
}

module_init(device_init);
module_exit(device_exit);
