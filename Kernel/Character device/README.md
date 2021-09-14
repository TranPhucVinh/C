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