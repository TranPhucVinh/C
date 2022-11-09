#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/poll.h>

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

#define OPEN_FLAG		1
#define READ_FLAG		2
#define WRITE_FLAG		3
#define CLOSE_FLAG		4

MODULE_LICENSE("GPL");

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

wait_queue_head_t waitqueue;

int dev_open(struct inode *, struct file *);
int dev_close(struct inode *, struct file *);
ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
unsigned int dev_poll(struct file *file, poll_table *wait);

int flag;

struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write,
	.poll = dev_poll,
};

int dev_open(struct inode *inodep, struct file *filep)
{
	flag = OPEN_FLAG;
	wake_up(&waitqueue);
	printk("open\n");
	return 0;
}

int dev_close(struct inode *inodep, struct file *filep)
{
	flag = CLOSE_FLAG;
	wake_up(&waitqueue);
	printk("close\n");
	return 0;
}

ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	flag = READ_FLAG;
	wake_up(&waitqueue);
	printk("read\n");
	return 0;
}

char data[100];
ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	flag = WRITE_FLAG;
	wake_up(&waitqueue);

	memset(data, 0, sizeof(data));
	copy_from_user(data, buf, len);
	printk("write data: %s\n", data);
	return sizeof(data);
}

unsigned int dev_poll(struct file *file, poll_table *wait){
	poll_wait(file, &waitqueue, wait);

	//All flag can be set to a flag, like POLLIN
	if ((flag == OPEN_FLAG) || (flag == READ_FLAG) || (flag == WRITE_FLAG) || (flag == CLOSE_FLAG)) {
		flag = 0;
		return POLLIN;
	}

	return 0;
}

int device_init(void)
{
	init_waitqueue_head(&waitqueue);/* Init waitqueue */

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