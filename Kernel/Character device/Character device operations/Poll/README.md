# API

## struct file_operations
For working with [poll in userspace as I/O multiplexing](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/IO%20multiplexing%20examples.md), ``poll`` is handled in ``struct file_operations``:

```c
struct file_operations {
    //Other operation go here
    unsigned int (*poll) (struct file *, struct poll_table_struct *);
    //Other operation go here
};
```

The ``poll_table_struct`` structure, the second argument to the poll method, is used within the kernel to implement the [poll](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/IO%20multiplexing%20examples.md) and select calls; it is declared in ``<linux/poll.h>``, which must be included by the driver source. Driver writers need know nothing about its internals and must use it as an ``opaque`` object; it is passed to the driver method so that every event queue that could wake up the process and change the status of the poll operation can be added to the ``poll_table`` structure by calling the function [poll_wait()](#poll_wait).
## poll_wait()
```c
void poll_wait(struct file *, wait_queue_head_t *, poll_table *);
```
Wait for event to be ready.
[wake_up()](../waitqueue/README.md#wait_event) is used to wake up the driver/kernel module from from its wait status in **poll_wait()**

Implementation of poll for userspace process - character device takes advantages of [waitqueue](../waitqueue/).

# Examples

Response those poll event from character device ([character_device_poll.c](character_device_poll.c)) to userspace process ([user_space_poll.c](user_space_poll.c)):

* POLLPRI for open()
* POLLIN for read()
* POLLOUT for write()
* POLLHUP for close()

**Program**
* [character_device_poll.c](character_device_poll.c)
* [user_space_poll.c](user_space_poll.c)