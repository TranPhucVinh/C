# Read and write system call to character device

[character_device_operations.c](character_device_operations.c) supports 2 features:

* Send data to the character device
* Read response data from character device

## Send data to the character device

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

## Read response data from character device

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

## Userspace program for 2-way communication with character device

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

## Character device as a FIFO

To make a character device working as a FIFO for 2 process to R/W:

```c
char fifo[100];

ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	int bytes_response = copy_to_user(buf, fifo, sizeof(fifo));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(fifo);
}

ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	memset(fifo, 0, sizeof(fifo));
	copy_from_user(fifo, buf, len);
	printk("String read from userspace: %s\n", fifo);
	return sizeof(fifo);
}
```

After successfully creating, simply R/W to that character device as a FIFO by 2 process with normal ``read()``/``write()`` functions.
