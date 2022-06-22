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
* ``const char *name``: the name of the associated device or driver, that name will appear in ``/proc/devices``

### struct cdev

``struct cdev``: character device struct

```c
int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
```

* ``num``: the first device number to which this device responds,
* ``count``: the number of device numbers that should be associated with the device

**Note**: If ``count = 0``, it means no device can associate with this character device. Then working with this character device like ``cat /dev/character_device_name`` or ``echo "Data" > /dev/character_device_name`` will gives error: ``No such device or address``.

### struct class

The driver creates/destroys the class using those APIs:

```c
struct class *class_create(struct module *owner, const char *name);
```

* ``struct module *owner``: pointer to the module that is to “own” this struct class
* ``const char *name``: pointer to a string for the name of this class, that name will appear in ``/sys/class/``.

```c
void class_destroy (struct class *cls);
```

### struct device

The driver creates the device nodes using those APIs:

```c
struct device *device_create(struct class *cls, struct device *parent, dev_t devt, void * drvdata, const char **fmt...);
```

``device_create`` will create a device and register it with ``sysfs``

* ``struct class *class``: pointer to the struct class that this device should be registered to
* ``struct device *parent``: pointer to the parent ``struct device`` of this new device, if any
* ``dev_t devt``: the ``dev_t`` for the char device to be added
* ``void *drvdata``: the data to be added to the device for callbacks
* ``const char *fmt``: string for the device’s name, the name that will appear on ``/dev``

```c
void device_destroy (struct class * class, dev_t devt);
```

### struct file_operations

```c
struct file_operations {
    struct module *owner;
    loff_t (*llseek) (struct file *, loff_t, int);
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);	
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
    int (*mmap) (struct file *, struct vm_area_struct *);
    int (*open) (struct inode *, struct file *);
    int (*release) (struct inode *, struct file *);
};
```

``file_operations write()`` function pointer mapped to the write operation from user space to kernel space, e.g ``echo "Data" > /dev/character_device_name`` 

``file_operations read()`` function pointer mapped to the read operation as kernel space response data to user space and userspace read that responsed data by ``cat /dev/character_device_name``

## linux/cdev.h

* ``copy_from_user()``: Copy a block of data from user space to kernel space

* ``copy_to_user()``: Copy a block of data from kernel space to user space
* 
```c
unsigned long __copy_to_user (	void __user * to, const void * from, unsigned long n);
```

* ``void __user * to``: Destination address, in user space.
* ``const void * from``: Source address, in kernel space.
* ``unsigned long n``: Number of bytes to copy.

Returns number of bytes that could not be copied. On success, this will be zero.
