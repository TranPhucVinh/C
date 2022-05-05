# API

# Examples

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