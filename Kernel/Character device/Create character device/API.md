# linux/fs.h functions

### register_chrdev()

Register a character device to kernel

```c
int register_chrdev(unsigned int major, const char *name, struct file_operations *fops);
```

After calling ``register_chrdev()``, the newly registered device will have an entry in ``/proc/devices``, and we can either make that newly register device to be the device file by ``mknod`` command.

### unregister_chrdev()

Unregister and destroy a character device

```c
void __unregister_chrdev(unsigned int major, unsigned int baseminor, unsigned int count, const char * name);

static inline void unregister_chrdev(unsigned int major, const char *name)
{
	__unregister_chrdev(major, 0, 256, name);
}
```

### register_chrdev_region()

``register_chrdev_region()`` will assign the identifiers. After assigning the identifiers, the character device will have to be initialized using the ``cdev_init()`` function and registered to the kernel using the ``cdev_add()`` function.

```c
int register_chrdev_region(dev_t dev_id, unsigned int count, char *name); // the kernel fills up the variable dev_t with the combination of the major number and the first minor number that we requested for.
void unregister_chrdev_region(dev_t dev_id, unsigned int count);
```

* ``count``: the number of minor numbers required
* ``name``: the name of the associated device or driver

### dev_t

The ``dev_t`` type is used to keep the identifiers of a device (both major and minor) and can be obtained using the ``MKDEV()`` macro

```c
#include <sys/sysmacros.h>

unsigned int major(dev_t dev);
unsigned int minor(dev_t dev);
```

A device ID consists of two parts: a major ID, identifying the class of the device, and a minor ID, identifying a specific instance of a device in that class. A device ID is represented using the type ``dev_t``.

```c
#include <linux/fs.h>

#define MAJOR(dev)	((unsigned int) ((dev) >> MINORBITS)) //Extract the major number
#define MINOR(dev)	((unsigned int) ((dev) & MINORMASK))  //Extract the minor number
#define MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))
```

With ``major`` and ``minor`` number, we can create a ``dev_t``.

### alloc_chrdev_region

Allocate/Register a range of char device numbers

```c
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
```

* ``dev_t *dev``: output parameter for first assigned number
* ``unsigned baseminor``: first of the requested range of minor numbers
* ``unsigned count``: the number of minor numbers required
* ``const char *name``: the name of the associated device or driver, that name will appear in ``/proc/devices``

# linux/fs.h structs

### struct cdev

``struct cdev``: character device struct

```c
int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
```

* ``num``: the first device number to which this device responds,
* ``count``: the number of device numbers that should be associated with the device

**Note**: If ``count = 0``, it means no device can associate with this character device. Then working with this character device like ``cat /dev/character_device_name`` or ``echo "Data" > /dev/character_device_name`` will gives error: ``No such device or address``.

```c
struct cdev * cdev_alloc(void);
```

Allocate dynamic memory for a character device as a struct pointer object

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

The ``/sys/class/`` directory offers a view of the device drivers grouped by classes.

For ``DEVICE_CLASS`` created by ``class_create()``, it will then have a folder in ``/sys/class/``.

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

``struct file``, defined in ``<linux/fs.h>``, is the second most important data structure used in device drivers. Note that a ``file`` has nothing to do with the ``FILEs`` of user-space programs. A ``FILE`` is defined in the C library and never appears in kernel code. A ``struct file``, on the other hand, is a kernel structure that never appears in user programs.

The ``file_operations`` structure is defined in ``linux/fs.h``, although some Linux Kernel headers don't require including ``linux/fs.h``.

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

# linux/cdev.h

* ``copy_from_user()``: Copy a block of data from user space to kernel space

* ``copy_to_user()``: Copy a block of data from kernel space to user space

```c
unsigned long copy_to_user(void __user * to, const void * from, unsigned long n);
```

* ``void __user * to``: Destination address, in user space.
* ``const void * from``: Source address, in kernel space.
* ``unsigned long n``: Number of bytes to copy.

Both ``copy_from_user()`` and ``copy_to_user()`` return the number of bytes that could not be copied, in that fail case, those 2 functions must return error ``EFAULT`` to userspace. On success, they will be zero.

# Debug

### dev_dbg()

Specific debug function for character device

```c
#define dev_dbg(dev, format, ...)
```

Build kernel module included ``dev_dgb()`` normally (don't need other flag). ``dev_dgb()`` will print out like ``printk()`` followed by specific flags.

**Example**: From [create_character_device_by_seperated_operations.c](https://github.com/TranPhucVinh/C/blob/master/Kernel/Character%20device/create_character_device_by_seperated_operations.c), add ``dev_dbg()`` to ``device_init()`` and ``device_exit()``:

```c
int device_init(void)
{
	if (create_character_device(DEVICE_NAME, DEVICE_CLASS, TOTAL_MINOR, BASE_MINOR, &dev_info, &fops)){
		printk("Unable to create character device %s\n", DEVICE_NAME);
		return -1;
	} else dev_dbg(dev_info.device, "Register character device %s successfully\n", DEVICE_NAME);
	return 0;
}

void device_exit(void)
{
	printk("Device %s remove\n", DEVICE_NAME);
    dev_dbg(dev_info.device, "Debug: %s removed successfully\n", DEVICE_NAME);
	destroy_character_device(&dev_info, TOTAL_MINOR);
}
```

**Result**

```
[1008276.383562] register successfully major now is: 510
[1008276.383819] fops_device_class fops_character_device: Register character device fops_character_device successfully
[1008388.789995] Device fops_character_device remove
[1008388.790000] fops_device_class fops_character_device: Debug: fops_character_device removed successfully
````
