# [Basic operations](Basic%20operations)

Character device basic operations includes:

* [Read and write system call to character device](Basic%20operations/README.md#read-and-write-system-call-to-character-device)
* [Userspace program for 2-way communication with character device](Basic%20operations/README.md#userspace-program-for-2-way-communication-with-character-device)
* [Character device as a FIFO](Basic%20operations/README.md#character-device-as-a-fifo)
* [struct file *private_data](Basic%20operations/README.md#struct-file-private_data)

# [ioctl](ioctl)

ioctl system call to character device includes:

* [Basic implementation with cmd and arg](ioctl#implementation)
* [ioctl macro](ioctl#ioctl-macro)

# [llseek](llseek.md)

``llseek()`` of ``struct file_operations`` will handle the ``lseek()`` system call from the userspace application to the kernel device.

# [poll](Poll)

poll file operation with character device includes:

* [Character device poll file operation handling from the corresponded userspace system call](Poll#api)
* [Send POLLIN revent from character device to userspace application when open, read, write, close operations are performed to this character device]()

# [Signal](Signal)

Communication between userspace and character device by signal includes:

# [waitqueue](waitqueue)

Communication between userspace and character device by waitqueue includes:

# [kobject and refcount](kobject%20and%20refcount.md)