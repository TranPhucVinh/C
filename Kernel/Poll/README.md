# API

For working with [poll in userspace as I/O multiplexing](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/IO%20multiplexing%20examples.md), ``poll`` is handled in ``struct file_operations``:

```c
struct file_operations {
    //Other operation go here
    unsigned int (*poll) (struct file *, struct poll_table_struct *);
    //Other operation go here
};
```

The ``poll_table`` structure, the second argument to the poll method, is used within the kernel to implement the poll and select calls; it is declared in ``<linux/poll.h>``, which must be included by the driver source. Driver writers need know nothing about its internals and must use it as an ``opaque`` object; it is passed to the driver method so that every event queue that could wake up the process and change the status of the poll operation can be added to the ``poll_table`` structure by calling the function ``poll_wait``:

```c
void poll_wait (struct file *, wait_queue_head_t *, poll_table *);
```

``wake_up()``: Wake up a driver from from its wait status

# Examples

Send ``POLLIN`` ``revent`` from kernel space to user space when open, read, write, close operations are performed:

* [character_device_poll.c](character_device_poll.c)
* [user_space_poll.c](user_space_poll.c)

**Note**: Only valid ``revent`` can be sent back from kernel space to user space. For example, if asking kernel space to send ``POLLPRI`` in open operation (as ``POLLPRI`` is not the real ``revent`` from the open operation), it still sends ``POLLIN`` back to user space. 

E.g:

```c
//character_device_poll.c
if (flag == OPEN_FLAG) {
		flag = 0;
		printk("OPEN_FLAG, POLLIN\n");
		return POLLPRI;
	}
```

```c
//user_space_poll.c

//Handle revent POLLPRI
fds.fd = fd;
fds.events = 0;
fds.events |= POLLIN;
fds.events |= POLLPRI;
int pret = poll(&fds, nfds, TIMEOUT);
```

Then in ``user_space_poll.c``, ``POLLIN`` is received.
