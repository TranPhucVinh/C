# Fundamental concepts

## Register a character device then makes it a device file

Program: [register_character_device.c](register_character_device.c)

After inserting the LKM created from this program, ``fops_character_device``, the newly registered device with major number ``90`` and minor number ``0`` will have an entry in ``/proc/devices``, and we can either make that newly register device to be the device file by ``mknod`` command.

``sudo mknod /dev/char_dev c 90 0``: Make device file ``char_dev`` from character device with major number ``90`` and minor number ``0``.

## Create character device

``create_character_device.c``: Create a new character device named ``Character device``.

After creating successfully, a new device is found on ``/dev``.

To create a new character device, change all names in ``alloc_chrdev_region()``, ``class_create`` and ``device_create()``. If they have the same name, a new character device belong to a kernel module can't be inserted.

To remove the character device: ``sudo rm /dev/character_device_name``

## Operation with character device

``character_device_operation.c`` supports 2 features:

* Send data to the character device
* Read response data from character device

### Send data to the character device

* Change permission of the character device: ``sudo chmod 777 /dev/character_device_name``
* Then ``echo "Hello, World !" > /dev/character_device_name``. As sending the data from user space (using ``echo Hello, World !``, with string ``Hello, World !`` is in userspace) to kernel space (print out with ``printk()``, use ``copy_from_user()`` to get that data/string from the user space.

**Note**: Function ``dev_write()`` now mapped to the write operation from user space to kernel space, e.g ``echo "Data" > /dev/character_device_name`` 

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

In terminal (userspace): Use ``cat /dev/character_device_name`` to read the reponse string sent from kernel space.

In ``character_device_operation``, use function ``copy_to_user()`` to get the string responsed from the kernel space to print out on user space

**Error**: If the response string have no ``\n``, userspace can't receive the string properly (e.g: ``cat /dev/character_device_name`` won't print out any string)

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

## Operation with character device by ioctl

[character_device_ioctl.c](character_device_ioctl.c) supports 2 features:

* Get ``cmd`` and ``arg`` values sent from user space process then print that value out
* Print out the PID of the userspace process that performs the ``ioctl()`` system call

User space program that communicate with ``character_device_ioctl.c``: [user_space_ioctl.c](user_space_ioctl.c)

[character_device_ioctl_macro.c](character_device_ioctl_macro.c) handles ``ioctl()`` system call from userspace with all ``ioctl`` macro ``_IO()``, ``_IOR()``, ``_IOW()``, ``_IOWR()`` and ``_IOW()`` with struct as argument

User space program that communicate with ``character_device_ioctl_macro.c``: [user_space_ioctl_macro.c](user_space_ioctl_macro.c)

## Handle interrupt for character device

### API

Except for the extra argument, ``devm_request_threaded_irq()`` takes the same arguments and performs the same function as ``request_irq()``.

```c
int devm_request_threaded_irq	(	
	struct device * 	dev,
	unsigned int 	irq,
	irq_handler_t 	handler,
	irq_handler_t 	thread_fn,
	unsigned long 	irqflags,
	const char * 	devname,
	void * 	dev_id 
)	
```

* ``thread_fn``: function to be called in a threaded interrupt context, ``NULL`` for devices which handle everythin

### Examples

**Example 1**

Count how many times the keyboard is pressed on Ubuntu by using interrupt 1

Program: [interrupt_for_character_device.c](interrupt_for_character_device.c)

**Example 2**

Features
* Handle interrupt 1 like in example 1
* Disable and enable interrupt 1 from userspace through ``ioctl()``

Kernel module program [disable_enable_interrupt_for_character_device.c](disable_enable_interrupt_for_character_device.c)

User space program [ioctl_disable_enable_interrupt.c](ioctl_disable_enable_interrupt.c)

# API

[API document](API.md)
