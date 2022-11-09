# Fundamental concepts

## Register a character device then makes it a device file

Program: [register_character_device.c](register_character_device.c)

After inserting the LKM created from this program, ``fops_character_device``, the newly registered device with major number ``90`` and minor number ``0`` will have an entry in ``/proc/devices`` file (``cat /proc/devices``), and we can either make that newly register device to be the device file by ``mknod`` command.

``sudo mknod /dev/char_dev c 90 0``: Make device file ``char_dev`` from character device with major number ``90`` and minor number ``0``.

``sudo rm /dev/char_dev``: Remove the character device

Register character device with ``register_chrdev_region()`` and unregister with ``unregister_chrdev_region()``:

```c
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define MAJOR_NUM       100
#define MINOR_NUM       0
#define TOTAL_MINOR     1
#define CHAR_NAME   	"Character device"

static struct cdev my_dev;

/*
	Other operations are like register_character_device.c
*/

int device_init(void)
{
    int ret;
    dev_t dev = MKDEV(MAJOR_NUM, MINOR_NUM);

    ret = register_chrdev_region(dev, TOTAL_MINOR, CHAR_NAME);
    if (ret < 0){
        printk("Unable to allocate major number %d\n", MAJOR_NUM);
        return ret;
    }

    cdev_init(&my_dev, &my_dev_fops);
    ret= cdev_add(&my_dev, dev, TOTAL_MINOR);
    if (ret < 0){
        unregister_chrdev_region(dev, TOTAL_MINOR);
        printk("Unable to add cdev\n");
        return ret;
    }

    return 0;
}

void device_exit(void)
{
    cdev_del(&my_dev);
    unregister_chrdev_region(MKDEV(MAJOR_NUM, MINOR_NUM), 1);
}

/*
	Other operations are like register_character_device.c
*/
```

After inserting this module, operations with ``mknod`` and ``rm`` are all like ``register_character_device.c``.

## Create character device

### Create character device by single operations

**Features**: Create a new character device named ``Character device``. All character devices related functions are put inside ``module_init()``  and ``module_exit()`` functions.  This example is intended for comprehensive and easy to understand the character device created operation.

**Program**: [create_character_device_by_single_operations.c](create_character_device_by_single_operations.c) 

After creating successfully, a new device is found on ``/dev``.

To create a new character device, change all names in ``alloc_chrdev_region()``, ``class_create`` and ``device_create()``. If they have the same name, a new character device belong to a kernel module can't be inserted.

To remove the character device: ``sudo rm /dev/character_device_name``

### Create character device by seperated operations

**Features**: Seperated the character device created operation by function ``create_character_device()`` and the destroy operations by function ``destroy_character_device()``. This program is intended for functions inheritance for other kernel modules.

**Program**: [create_character_device_by_seperated_operations.c](create_character_device_by_seperated_operations.c)

## Read and write system call to character device

[character_device_operations.c](character_device_operations.c) supports 2 features:

* Send data to the character device
* Read response data from character device

### Send data to the character device

* Change permission of the character device: ``sudo chmod 777 /dev/fops_character_device``
* Then ``echo "Hello, World !" > /dev/fops_character_device``. As sending the data from user space (using ``echo Hello, World !``, with string ``Hello, World !`` is in userspace) to kernel space (print out with ``printk()``, use ``copy_from_user()`` to get that data/string from the user space.

**Note**: Function ``dev_write()`` now mapped to the write operation from user space to kernel space, e.g ``echo "Data" > /dev/fops_character_device`` 

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

### Read response data from character device

In terminal (userspace): Use ``cat /dev/fops_character_device`` to read the reponse string sent from kernel space.

In ``character_device_operation``, use function ``copy_to_user()`` to get the string responsed from the kernel space to print out on user space

**Error**: If the response string have no ``\n``, userspace can't receive the string properly (e.g: ``cat /dev/fops_character_device`` won't print out any string)

```c
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	/*
		Must have \n for proper sending as user read with cat /dev/character_device
		without \n, cat /dev/character_device will read empty
	*/
	char responsed_string[] = "Response string from kernel space to user space\n";
	int bytes_response = copy_to_user(buf, responsed_string, sizeof(responsed_string));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(responsed_string);
}
```

### Userspace program for 2-way communication with character device

Program [user_space_2_way_communications.c](user_space_2_way_communications.c) supports 2-way communications R/W between userspace and character device.

**Note**

If calling only ``open()`` system call in a userspace process like this program (without ``close()`` system call):

```c
int main(){
    int fd = open("/dev/fops_character_device", O_RDONLY);
   	//There is no close() system call here
}
```

Then both file operation open (``dev_open()``) and close (``dev_close()``) are called in the character device after that userspace process finishes running, as the OS will automatically close the device file which will trigger the close file operation.

### Handle specific error from errno from userspace

To handle any specific errno like ``EBUSY`` on character device, that device must handle this error in its operation, like the open operation:

```c
int open_flag = 0;

//This is file open operation for character device
int dev_open(struct inode *inodep, struct file *filep)
{
	if (open_flag == 0)	{
		open_flag = 1;
		return 0;
	}
	if (open_flag == 1)	{
		printk("Device is already open\n");
		open_flag = 0;
		return -EBUSY;
	}
	return 0;
}
```

Check [this source code](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/fcntl.md#ebusy) for the userspace process to handle this EBUSY error.

## Handle interrupt for character device

Check [document and examples in Interrupt folder](../Interrupt/).

# API

[API document](API.md)
