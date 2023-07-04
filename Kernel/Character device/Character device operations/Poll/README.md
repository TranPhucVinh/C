# API

## struct file_operations
For working with [poll in userspace as I/O multiplexing](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/System%20call/poll), ``poll`` is handled in ``struct file_operations``:

```c
struct file_operations {
    //Other operation go here
    unsigned int (*poll) (struct file *, struct poll_table_struct *);
    //Other operation go here
};
```

The ``poll_table_struct`` structure, the second argument to the poll method, is used within the kernel to implement the [poll](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/System%20call/poll) and select calls; it is declared in ``<linux/poll.h>``, which must be included by the driver source. Driver writers need know nothing about its internals and must use it as an ``opaque`` object; it is passed to the driver method so that every event queue that could wake up the process and change the status of the poll operation can be added to the ``poll_table`` structure by calling the function [poll_wait()](#poll_wait).
## poll_wait()
```c
void poll_wait(struct file *, wait_queue_head_t *, poll_table *);
```
Wait for event to be ready.
[wake_up()](../waitqueue/README.md#wait_event) is used to wake up the driver/kernel module from from its wait status in **poll_wait()**

Implementation of poll for userspace process - character device takes advantages of [waitqueue](../waitqueue/).

# Implementations
## poll handling in character device

Response those poll event from character device ([character_device_poll.c](character_device_poll.c)) to userspace process ([user_space_poll.c](user_space_poll.c)):

* POLLPRI for open()
* POLLIN for read()
* POLLOUT for write()
* POLLHUP for close()

**Program**
* [character_device_poll.c](character_device_poll.c)
* [user_space_poll.c](user_space_poll.c)

**Result**:

```sh
$ ./user_space_poll
Open /dev/fops_character_device successfully 
open() to get POLLPRI from /dev/fops_character_device # open() of user_space_poll
# Run cat /dev/fops_character_device in the 2nd terminal to get those 3 responses
open() to get POLLPRI from /dev/fops_character_device # open() of cat /dev/fops_character_device
read() to get POLLIN from /dev/fops_character_device # read() of cat /dev/fops_character_device
close() to get POLLHUP from /dev/fops_character_device # close() of cat /dev/fops_character_device
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
# Run echo "any string" > /dev/fops_character_device in the 2nd terminal to get those 3 responses
open() to get POLLPRI from /dev/fops_character_device # open() of echo "any string" > /dev/fops_character_device
write() to get POLLOUT from /dev/fops_character_device # write() of echo "any string" > /dev/fops_character_device
close() to get POLLHUP from /dev/fops_character_device # write() of echo "any string" > /dev/fops_character_device
```
## epoll handling in character device: Response any events to the userspace process

Response those epoll event from character device ([character_device_epoll.c](character_device_epoll.c)) to userspace process ([user_space_epoll.c](user_space_epoll.c)):

* EPOLLET for open()
* EPOLLIN for read()
* EPOLLOUT for write()
* EPOLLHUP for close()

All those epoll events are only supported in Linux kernel > 5.0. Ubuntu 16.04 with 4.15.0-142-generic doesn't supported those epoll events.

[character_device_epoll.c](character_device_epoll.c) is an echo character device which responsed to read() system call the string previously written to it (by write() system call)

**Program**
* [character_device_epoll.c](character_device_epoll.c)
* [user_space_epoll.c](user_space_epoll.c)

**Result**
```sh
$ ./user_space_epoll
Timeout after 5000 miliseconds
# Run echo "any string" > /dev/fops_character_device in the 2nd terminal to get those 3 responses
open() to get EPOLLET from /dev/fops_character_device
write() to get EPOLLOUT from /dev/fops_character_device
close() to get EPOLLHUP from /dev/fops_character_device
Timeout after 5000 miliseconds
# Run cat /dev/fops_character_device in the 2nd terminal to get those 3 responses
open() to get EPOLLET from /dev/fops_character_device
read() to get EPOLLIN from /dev/fops_character_device
close() to get EPOLLHUP from /dev/fops_character_device
```
## epoll handling in character device: Monitor EPOLLIN event for write() system call/cat command

* cat command/write() system call will write a string to character device, which also trigger EPOLLIN event.
* Userspace program monitors EPOLLIN event of character device. When userspace program catches that EPOLLIN event from the character device, it will read the string previously written to this character device.

**Program**
* [character_device_epollin.c](character_device_epollin.c)
* [user_space_epollin.c](user_space_epollin.c)

Userspace program to monitor EPOLLIN in multiple character device:
* Character device: Create 2 character devices char_dev_1 and char_dev_2 from [character_device_epollin.c](character_device_epollin.c)
* Userspace program: [user_space_epollin_multi_char_dev.c](user_space_epollin_multi_char_dev.c)
