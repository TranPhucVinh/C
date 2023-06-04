#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/slab.h> //for kmalloc()

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"
#define TOTAL_MINOR                1
#define BASE_MINOR				   0

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

char    *data;
int     responsed_size;// Store the size of (char *data) for R/W system call
int     flag;

struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write,
	.poll = dev_poll,
};

int dev_open(struct inode *inodep, struct file *filep)
{
	flag = EPOLLET;
	wake_up(&waitqueue);
	printk("open(); flag = EPOLLET\n");
	return 0;
}

int dev_close(struct inode *inodep, struct file *filep)
{
	flag = EPOLLHUP;
	wake_up(&waitqueue);
	printk("close(); flag = EPOLLHUP\n");
	return 0;
}

// Must have proper resposnsed string for cat command from userspace to trigger read() systemcall
ssize_t dev_read(struct file *filep, char __user *buf, size_t len, loff_t *offset)
{
    flag = EPOLLIN;
    wake_up(&waitqueue);
    if(*offset > 0) return 0; /* End of file */
	else {
		int bytes_response = copy_to_user(buf, data, responsed_size);
		if (!bytes_response){
			printk("Responsed string to userpsace has been sent\n");
			*offset = responsed_size;
			return *offset;
		} else {
			printk("%d bytes could not be send\n", bytes_response);
			return -1;
		}
	}
}

ssize_t dev_write(struct file *filep, const char __user *buf, size_t len, loff_t *offset)
{
	flag = EPOLLOUT;
	wake_up(&waitqueue);

	kfree(data);
    data = (char*) kzalloc(len, GFP_KERNEL);
    copy_from_user(data, buf, len);
	printk("String read from userspace: %s\n", data);

    responsed_size = len;
	return responsed_size;
}

unsigned int dev_poll(struct file *filep, poll_table *wait){
	poll_wait(filep, &waitqueue, wait);
	int responsed_flag = flag;

	// Reset flag; if not resetting, flag will keep its old value after a POLL event is triggered
	flag = 0;
	return responsed_flag;
}

int device_init(void)
{
	init_waitqueue_head(&waitqueue);/* Init waitqueue */

	int ret;

	ret = alloc_chrdev_region(&dev_id, BASE_MINOR, TOTAL_MINOR, "fops_alloc_chrdev_region");
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