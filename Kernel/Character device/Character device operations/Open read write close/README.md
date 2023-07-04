# Read system call to character device

``ssize_t dev_read()`` function of ``struct file_operations`` will handle the read() system call from userspace:

```c
ssize_t dev_read(struct file *filep, char __user *buf, size_t len, loff_t *offset);
```
* [struct file *filep](#data-structures-maintained-by-the-kernel-for-file-io)
* ``char __user *buf``: Buffer of the userspace application which involves the ``read()`` sytem call
* ``size_t len``: Length/size of the userspace buffer (``char __user *buf``), i.e ``size_t len`` of ``dev_read()`` in character device is able to get the size of the userspace buffer of the read() system call.
* [loff_t *offset](../llseek.md)

Userspace application with ``read()`` system call:

```c
#define RD_SIZE 30

char buffer[RD_SIZE];

int fd;

int main(){
    fd = open(CHAR_DEV, O_RDWR);
    if(fd < 0) {
        printf("Fail to open %s\n",CHAR_DEV);
        return 1;
    }
    else {
        while(1){  
            read(fd, buffer, sizeof(buffer));
            sleep(1);
        }
        close(fd);
        return 0;     
    }
}
```

Character device with ``dev_read()`` function like this will print out the size of the userspace buffer of the ``read()`` system call, like the userspace application above:
```c
ssize_t dev_read(struct file *filep, char __user *buf, size_t len, loff_t *offset)
{
	// char responsed_string[] = "Response string from kernel space to user space";
	printk("read() size_t len %d\n", len);
	return 0;
}
```
Result in dmesg:
```
[ 2173.646379] read() size_t len 30
[ 2174.646754] read() size_t len 30
...
```
# Read and write system call to character device

[character_device_operations.c](character_device_operations.c) supports 2 features:

* Send data to the character device
* Read response data from character device

## Send data to the character device

* Change permission of the character device: ``sudo chmod 777 /dev/fops_character_device``
* Then ``echo "Hello, World !" > /dev/fops_character_device``. As sending the data from user space (using ``echo Hello, World !``, with string ``Hello, World !`` is in userspace) to kernel space (print out with ``printk()``), use ``copy_from_user()`` to 

**Note**: Function ``dev_write()`` now mapped to the write operation from user space to kernel space, e.g ``echo "Data" > /dev/fops_character_device`` 

**Error**: If ``dev_write()`` function returns ``0``, there will be error as using ``echo`` to send data will result in the infinite loop.

```c
char data[100];
/*
    This function gives infinite loop error
*/
ssize_t dev_write(struct file *filep, const char __user *buf, size_t len, loff_t *offset)
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

### Error: Infinite read from [cat](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/File%20system/Read%20operations.md#cat)

With ``dev_read()`` function definition's like below, ``cat /dev/fops_character_device`` will result in infinite read of the responsed string ``responsed_string[]``:

```c
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	char responsed_string[] = "Response string from kernel space to user space\n";
	int bytes_response = copy_to_user(buf, responsed_string, sizeof(responsed_string));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(responsed_string);
}
```
That happens as [cat](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/File%20system/Read%20operations.md#cat) continually reads until it gets an empty response. Once it finished getting some data, it goes back and asks whether there are still data left.

This issue must be solved by using ``loff_t *offset`` argument of ``dev_read()``, which accesses to the offset of the current device file of the character device.
### Using [llseek()](../llseek.md) is mandatory to support multiple read() system call

As [dev_read](character_device_operations.c#L51) has updated the ``*offset`` to fix the [infinite read from cat](#error-infinite-read-from-cat), [dev_llseek()](character_device_operations.c#L81) must be used to changed the offset back to 0 for next time calling [read() in the userspace program](user_space_2_way_communications.c#L27).

[lseek() must also be used in the userspace program](user_space_2_way_communications.c#L25) to change the offset back to 0 in [the responsed string of the character device](character_device_operations.c#L22).

# Userspace program for 2-way communication with character device

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

# echo character device

**Features**:
* Character device responses the string written to it previously
* Use dynamic allocation to allocate [char *data](echo_character_device.c#L69) which is used to store the string written from the userspace (write() system call) then response/echo (read() system call) back to userspace.
* **Note**: Note on [dev_write()](echo_character_device.c#L66) function which returns the length of the string written from the userspace, not returning sizeof(data) as there is no portable way to find out the size of a kmalloc'ed block.

**Program**: [echo_character_device.c](echo_character_device.c)

# Data structures maintained by the kernel for file IO
From the API and implementation seen above, there are three data structures maintained by the kernel for file IO:
* the per-process file descriptor table: ``struct file *filep``
* the system-wide table of open file descriptions
* the file system i-node table: ``struct inode *inodep``

## struct file *private_data

Every struct file object of the ``struct file_operations`` functions like open(), read(), write() and release() functions of a character device share ``private_data``, a void pointer. ``void *private_data`` of ``struct file`` can be used to share between those functions and returned to the userspace.

Program to share ``private_data`` between ``struct file_operations`` functions like open() and read() functions (also return data to the userspace)

```c
//Other part of the program are like character_device_operations.c
/*
	User char array for string to later get its size by sizeof()
	Like malloc(), there is no way to get the size of the kmalloc() block
*/
char private_data[] = "Character device private data 2023 29/3";
int dev_open(struct inode *inodep, struct file *filep)
{
	printk("open\n");
	filep->private_data = (char*) kstrdup(private_data, GFP_KERNEL);
	printk("%s, sizeof() %d\n", filep->private_data, sizeof(private_data));
	return 0;
}
int dev_close(struct inode *inodep, struct file *filep)
{
	printk("close\n");
	kfree(filep->private_data);
	return 0;
}
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	int bytes_response = copy_to_user(buf, filep->private_data, sizeof(private_data));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(private_data);
}
```
