# [Basic operations](Basic%20operations)

Character device basic operations includes:

* [Read and write system call to character device]()
* [Userspace program for 2-way communication with character device]()
* [Character device as a FIFO]()

# [ioctl](ioctl)

ioctl system call to character device includes:

* [Basic implementation with cmd and arg](ioctl#implementation)
* [ioctl macro](ioctl#ioctl-macro)

# [poll](Poll)

poll file operation with character device includes:

# [Signal](Signal)

Communication between userspace and character device by signal includes:

# [waitqueue](waitqueue)

Communication between userspace and character device by waitqueue includes:

# kobject and refcount

The ``kobject`` is the glue that holds much of the device model and its [sysfs]() interface together. 

Every ``kobject`` has a reference count (``refcount``). After initialization, the kobject's reference count is set to ``1``. So long as the reference count is nonzero, the object continues to exist in memory and is said to be pinned. Any code that holds a reference to the object first elevates the reference count. When the code is finished with the object, the reference count is decremented. Bumping the reference count is called getting a reference to the object, and decrementing the reference count is called putting reference to the object.

## API

```c
struct kobject {
	const char		*name;
	struct list_head	entry;
	...
	struct kref		kref;
    ...
};
```

```c
struct kref {
    atomic_t refcount;
};
```

## Implementation

### In character device

In a character device, function ``module_refcount()`` will return the current ``refcount`` value. As stated before, when a character device/kernel module is created, it will have ``refcount = 1``.

```c
int create_character_device(const char* dev_name, const char* dev_class, int total_minor, int base_minor, struct chr_dev_info *dev_info, struct file_operations *fops){
    //Full program: create_character_device_by_seperated_operations.c
	printk("%s has reference count %d\n", THIS_MODULE->name, module_refcount(THIS_MODULE));
}
```

**Result**

```
ubuntu_kernel_module has reference count 1
```

After creating the character device, the refcount will be increased to ``1`` so that ``refcount = 1``. Then after creating successfully, ``refcount`` will then decrease to ``0``.

Userspace program ``user_space.c`` that holds reference to the object like ``open()`` system call will increase the ``refcount`` to ``1``:

```c
#define CHAR_DEV     "/dev/fops_character_device"

int fd = open(CHAR_DEV, O_RDWR);

/*
	Keep the character device open in this program by while() so that the refcount 
	handle by that character device open function will be kept to be displayed by
	dmesg
*/
while (fd > 0){
	sleep(1);
}
```

Character device file open function handler to view the ``refcount``:

```c
int dev_open(struct inode *inodep, struct file *filep)
{
	printk("open systemcall %s has reference count %d\n", THIS_MODULE->name, module_refcount(THIS_MODULE));
	return 0;
}
```

Every time running a process built from ``user_space.c``, the ``refcount`` of ``/dev/fops_character_device`` will be increased by ``1``.

### In sysfs

[sysfs entry](../../sysfs%20entry.md) requires kboject when creating it.