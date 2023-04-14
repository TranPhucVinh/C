``llseek()`` of ``struct file_operations`` will handle the ``lseek()`` system call from the userspace application to the kernel device.

The ``loff_t *offset`` arguments of all ``dev_read()``, ``dev_write()``, and ``dev_llseek()`` access to the offset of the current device file of the character device, i.e ``loff_t *offset`` arguments of those 3 functions are the same/have the same value.

With ``lseek()`` system call from userspace, we can modify the value of the ``loff_t *offset`` argument of ``dev_llseek()`` so that this argument will take effect in the ``dev_write()`` and ``dev_read()``.

# Implement llseek()

## Features

* Userspace program reads the returned string from character device at specific ``index`` by using ``lseek()`` system call.
* Character device handles ``lseek()`` system call (with the specific ``index``) by ``dev_llseek()`` to set the ``loff_t *offset`` value. ``dev_read()`` will responsed the string to the userspace program at the specified ``index`` based on the ``loff_t *offset`` value.

## Character device

Main program structure based on [character_device_operations.c](../Character%20device%20operations/Basic%20operations/character_device_operations.c)

```c
//Other part of the program are like character_device_operations.c
loff_t dev_llseek(struct file *, loff_t, int);

struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write,
	.llseek = dev_llseek,
};

char responsed_string[] = "1234567890111213Hello, World !\n";
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	int bytes_response = copy_to_user(buf, responsed_string + *offset, sizeof(responsed_string) - *offset);
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(responsed_string) - *offset;
}

loff_t dev_llseek(struct file *filep, loff_t offset, int whence){
	loff_t newpos;

    switch(whence) {
        case SEEK_SET:
            newpos = offset;
            break;
    
        case SEEK_END:
            newpos = sizeof(responsed_string) - offset;
            break;

        default:
            return -EINVAL;
    }
    if (newpos < 0) return -EINVAL;

    filep->f_pos = newpos;// Change the position to newpos
    return newpos;
}
//Other part of the program are like character_device_operations.c
```

## Userspace program

```c
#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 

int main() 
{ 
    int fd;
    char buffer[100];

    fd = open("/dev/fops_character_device", O_RDONLY);
    int offset = lseek(fd, 3, SEEK_SET);
    printf("offset %d\n", offset);//3
    if (offset > 0){
        read(fd, buffer, 100);
        printf("%s\n", buffer);
    }
    return 0; 
}
```
For ``index=3`` like above, the result will be:

```
4567890111213Hello, World !
```
# nonseekable_open()

To inform the kernel that the character device file is not allow seekable (i.e lseek() system call is not allowed), add ``nonseekable_open()`` to ``struct file_operations open``.

```c
int dev_open(struct inode *inodep, struct file *filep)
{
  printk("open\n");
	return nonseekable_open(inodep, filep);
}
```
From user space process with ``lseek()`` system call like this ``int offset = lseek(fd, 3, SEEK_SET)``, ``offset`` will be ``-1``.

After adding ``nonseekable_open(inodep, filep)``, it's better to add built-in function ``no_llseek`` to ``struct file_operations .llseek``

```c
struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
	.read = dev_read,
	.write = dev_write,
	.llseek = no_llseek, //Don't add definition for no_llseek in character_device program as it's a built-in function defined in linux/fs.h
};
```
Definition in ``linux/fs.h``:

```c
loff_t no_llseek(struct file *file, loff_t offset, int whence)
{
	return -ESPIPE;
}
```