#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/sched/signal.h>

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

#define SIGNAL                      SIGUSR1

MODULE_LICENSE("GPL");

struct task_struct *userspace_process;

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

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

    struct siginfo info;

    userspace_process = get_current(); //set value for the userspace_process variable for later response to userspace

    info.si_signo = SIGNAL;

    /* Send SIGNAL to userspace process as response */
    if(send_sig_info(SIGNAL, (struct kernel_siginfo *) &info, userspace_process) < 0) {
        printk("Error sending signal\n");
	} else printk("Response signal %d successfully\n", SIGNAL);

	return 0;
}

int dev_close(struct inode *inodep, struct file *filep)
{
	printk("close\n");
	return 0;
}

/*
	It's better to handle the read operation properly from userspace with 
	copy_to_user() and return sizeof(). This will help other operation from
	user space like cat command
*/
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
    char responsed_string[] = "Response string from kernel space to user space\n";
	int bytes_response = copy_to_user(buf, responsed_string, sizeof(responsed_string));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(responsed_string);
}

/*
	It's better to handle the write operation properly from userspace with 
	copy_from_user() and return sizeof().
*/
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