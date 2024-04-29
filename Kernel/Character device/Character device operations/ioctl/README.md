# Implementation

[character_device_ioctl.c](character_device_ioctl.c) supports 2 features:

* Get ``cmd`` and ``arg`` values sent from user space process then print that value out
* Print out the PID of the userspace process that performs the ``ioctl()`` system call

User space program that communicate with ``character_device_ioctl.c``: [user_space_ioctl.c](user_space_ioctl.c)

**Note**: If sending ``argument`` (the 3rd parameters of ``ioctl()``) with no ampersand, the ``EFAULT`` error is responsed from ``character_device_ioctl.c`` kernel module (by function ``copy_from_user()``:

```c
//This sending is wrong and EFAULT is responsed from the kernel module
if (ioctl(fd, cmd, argument) == -1) {}
```
**Result**

```
DEBUG: Bad address
Error number: 14
```

[character_device_ioctl_macro.c](character_device_ioctl_macro.c) handles ``ioctl()`` system call from userspace with all ``ioctl`` macro ``_IO()``, ``_IOR()``, ``_IOW()``, ``_IOWR()`` and ``_IOW()`` with struct as argument

User space program that communicate with ``character_device_ioctl_macro.c``: [user_space_ioctl_macro.c](user_space_ioctl_macro.c)

# API
## long dev_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
* **arg**: Address of the user-space argument
## ioctl macro

* ``_IO(int type, int number)``: used for a simple ioctl that sends nothing but the ``type`` and ``number``, and receives back nothing but an (integer) ``retval``

* ``_IOR(int type, int number, data_type)``: used for an ioctl that reads data from the device driver. The driver will be allowed to return ``sizeof(data_type)`` bytes to the user

* ``_IOW(int type, int number, data_type)``: similar to ``_IOR``, but used to write data to the driver

* ``_IOWR(int type, int number, data_type)``: a combination of ``_IOW`` and ``_IOR``. That is, data is both written to the driver and then read back from the driver by user

**Parameters**:

* ``type``, an 8-bit integer selected to be specific to the device driver. ``type`` should be chosen so as not to conflict with other drivers that might be listening to the same file descriptor.
* ``number``, an 8-bit integer command number. Within a driver, distinct numbers should be chosen for each different kind of ioctl command that the driver services
* ``data_type``, the name of a type used to compute how many bytes are exchanged between the client and the driver. This argument is, for example, the name of a structure.
