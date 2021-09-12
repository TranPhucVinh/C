## Examples

* ``create_character_device.c``: Create a new character device named ``Character device``.

After creating successfully, a new device is found on ``/dev``.

To create a new character device, change all names in ``alloc_chrdev_region()``, ``class_create`` and ``device_create()``. If they have the same name, a new character device belong to a kernel module can't be inserted.

To remove the character device: ``sudo rm /dev/character_device_name``

* ``character_device_operation.c``: Operation with character device

To send data to the character device: ``echo "Hello, World !" > /dev/character_device_name``

**Error**: If ``dev_write()`` function return 0, there will be error as using ``echo`` to send data will result in the infinite loop.

```c
char data[100];
/*
    This function gives infinite loop error
*/
ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	memset(data, 0, sizeof(data));
	copy_from_user(data, buf, len);
	printk("write data: %s\n", data);
	return 0;
}
```
**Explain**

This happen as the write system call (``dev_write()``) returns to userspace with ``0``. However, since your userspace code is using ``stdio``, then your userspace code tries the write again, assuming the system call simply didn't write out all the data. If you return the length of the input, then stdio will know all the data was written.

## API

### dev_t

```c
#include <sys/sysmacros.h>

dev_t makedev(unsigned int maj, unsigned int min);

unsigned int major(dev_t dev);
unsigned int minor(dev_t dev);
```

A device ID consists of two parts: a major ID, identifying the class of the device, and a minor ID, identifying a specific instance of a device in that class. A device ID is represented using the type ``dev_t``.

### alloc_chrdev_region

Allocate/Register a range of char device numbers

```c
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
```

* ``dev_t *dev``: output parameter for first assigned number
* ``unsigned baseminor``: first of the requested range of minor numbers
* ``unsigned count``: the number of minor numbers required
* ``const char *name``: the name of the associated device or driver

### struct cdev

``struct cdev``: character device struct

```c
int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
```

* ``num``: the first device number to which this device responds,
* ``count``: the number of device numbers that should be associated with the device

**Note**: If ``count = 0``, it means no device can associate with this character device. Then working with this character device like ``cat /dev/character_device_name`` or ``echo "Data" > /dev/character_device_name`` will gives error: ``No such device or address``.

### struct class

```c
struct class *class_create(struct module *owner, const char *name);
```

* ``struct module *owner``: pointer to the module that is to “own” this struct class
* ``const char *name``: pointer to a string for the name of this class.

### struct device

```c
struct device *device_create(struct class *cls, struct device *parent, dev_t devt, void * drvdata, const char **fmt...);
```

* ``struct class *class``: pointer to the struct class that this device should be registered to
* ``struct device *parent``: pointer to the parent ``struct device`` of this new device, if any
* ``dev_t devt``: the ``dev_t`` for the char device to be added
* ``void *drvdata``: the data to be added to the device for callbacks
* ``const char *fmt``: string for the device’s name, the name that will appear on ``/dev``

## linux/cdev.h

* ``copy_from_user()``