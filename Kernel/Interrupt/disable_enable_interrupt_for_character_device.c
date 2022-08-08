#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/interrupt.h>

#define INTERRUPT_NAME              "INTERRUPT_NAME IRQ_1"
#define INTERRUPT_ID        "INTERRUPT_ID"

#define DEVICE_NAME					"fops_character_device"
#define DEVICE_CLASS				"fops_device_class"

#define DISABLE_IRQ          _IO('d', 0)
#define ENABLE_IRQ           _IO('e', 0)

#define THREAD_FN           NULL
#define IRQ_NUM		        1

MODULE_LICENSE("GPL");

int pressed_times = 0;

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

int dev_open(struct inode *, struct file *);
int dev_close(struct inode *, struct file *);
ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
long dev_ioctl(struct file *, unsigned int cmd, unsigned long arg);

irq_handler_t irq_1_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
	printk("Interrupt ID: %s; keyboard interrupt occured %d times\n",  (char*)dev_id, pressed_times);
	pressed_times += 1;
    return (irq_handler_t) IRQ_HANDLED;
}

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
	char usr_arg[30];

	copy_from_user(usr_arg, (char*)arg, sizeof(usr_arg));

	switch (cmd){
		case DISABLE_IRQ:
			printk("DISABLE_IRQ: cmd %d, arg %s\n", cmd, usr_arg);
            disable_irq(IRQ_NUM);
			break;
		case ENABLE_IRQ:
            enable_irq(IRQ_NUM);
			printk("ENABLE_IRQ: cmd %d, arg %s\n", cmd, usr_arg);
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

    if (devm_request_threaded_irq(device, IRQ_NUM, (irq_handler_t) irq_1_handler, (irq_handler_t) THREAD_FN, IRQF_SHARED, INTERRUPT_NAME, INTERRUPT_ID) != 0){
        printk("Can't request interrupt number %d\n", IRQ_NUM);
    } else printk("Request interrupt number %d successfully\n", IRQ_NUM);

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
