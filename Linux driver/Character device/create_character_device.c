#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

int device_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev_id, 0, 1, "alloc_chrdev_region");
	if(ret)
	{
		printk("can not register major no\n");
		return ret;
	}
	printk(KERN_INFO "register successfully major now is: %d\n", MAJOR(dev_id));
	character_device = cdev_alloc();
	character_device->owner = THIS_MODULE;
	character_device->dev = dev_id;
	cdev_add(character_device, dev_id, 0);
	device_class = class_create(THIS_MODULE, "Device class name");
	device = device_create(device_class, NULL, dev_id, NULL, "Character device");

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
