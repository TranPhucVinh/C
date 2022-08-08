#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define INTERRUPT_NAME    "INTERRUPT_NAME IRQ_1"

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

#define THREAD_FN        NULL
#define IRQ_1		1

#define TOTAL_MINOR                1
#define BASE_MINOR				   0

MODULE_LICENSE("GPL");

int pressed_times = 0;

irq_handler_t irq_1_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
	printk("devm_request_threaded_irq; keyboard interrupt occured %d times\n", pressed_times);
	pressed_times += 1;
    return (irq_handler_t) IRQ_HANDLED;
}

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

int init_module(void)
{
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

    if (devm_request_threaded_irq(device, IRQ_1, (irq_handler_t) irq_1_handler, (irq_handler_t) THREAD_FN, IRQF_SHARED, INTERRUPT_NAME, (void*)irq_1_handler) != 0){
        printk("Can't request interrupt number %d\n", IRQ_1);
    } else printk("Request interrupt number %d successfully\n", IRQ_1);

	return 0;
}

void cleanup_module(void)
{
    /*
       	devm_free_irq() must go with devm_request_threaded_irq() function
		to avoid memory issue with IRQ when performing insmod and rmmod
		for the module several times.
    */
	devm_free_irq(device, IRQ_1, (void*)irq_1_handler);
	unregister_chrdev_region(dev_id, TOTAL_MINOR); 
	cdev_del(character_device);
	device_destroy(device_class, dev_id);
	class_destroy(device_class);
	printk(KERN_INFO "clean up module\n");
}
