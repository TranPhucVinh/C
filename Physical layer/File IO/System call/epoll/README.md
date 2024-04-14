The epoll API performs a similar task to ``poll()`` as monitoring multiple file descriptors to see if I/O is possible on any of them. 

# API

## Two lists

The central concept of the ``epoll`` API is the epoll instance, an in-kernel data structure which, from a user-space perspective, can be considered as a container for two lists:

* The **interest** list (sometimes also called the **epoll set**): the set of file descriptors that the process has registered an interest in monitoring.
* The **ready** list: the set of file descriptors that are "ready" for I/O.

## epoll_create()

```c
#include <sys/epoll.h>
int epoll_create1(int flags);
```

``epoll_create1()`` creates a new ``epoll()`` instance and returns a file descriptor ``efd`` referring to the new ``epoll`` instance.

* ``flags``: This argument takes only 1 value ``EPOLL_CLOEXEC`` as set the close-on-exec flag on the new file descriptor.

``epoll_create()`` is an older variant of ``epoll_create1()`` and is deprecated.

## epoll_wait()
The **epoll_wait()** system call waits for events on the ``epoll()`` instance referred to by the file descriptor ``epfd``:
```c
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```
* ``maxevents``: the maximum number of epoll_event/file descriptors to be monitored **concurrently**. Should be set to the size of the ``struct epoll_event *events`` array.

**Concurrently** means that epoll can handle maximum **maxevents** file descriptors with the monitored event at the same time. **E.g**:

With ``maxevents = 5`` and the monitored event is **EPOLLIN**, when there are 6 monitored file descriptors with event **EPOLLIN** happen, only 5 among those 6 file descriptors are handled.

**Concurrently** also means that epoll can handle more than **maxevents** file descriptors with the monitored event as long as the monitored event of those file descriptors happen **respectively**, **not concurrently**

**E.g**: With ``maxevents = 1`` and the monitored event is **EPOLLIN**, when there are more than 1 monitored file descriptors with event **EPOLLIN** happen respectively, those file descriptors are handled properly by epoll.

**Return**:
* the number of file descriptors ready for the requested I/O when **success**
* ``0``: no file descriptor became ready during the requested ``timeout`` milliseconds.
* ``-1``: Error and [errno](https://github.com/TranPhucVinh/C/tree/master/Introduction#error-handling) is set to indicate the error.

## epoll_ctl()

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

``epoll_ctl()`` system call is used to add, modify, or remove entries in **the interest list** of the ``epoll()`` instance referred to by the file descriptor ``epfd``.

## struct

```c
typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;
```

```c
struct epoll_event {
    uint32_t     events;      /* Epoll events */
    epoll_data_t data;        /* User data variable */
};
```

The ``events`` member of the ``epoll_event`` structure is a bit mask composed by ORing together zero or more of the available **event types** like **EPOLLIN**, **EPOLLOUT**,...

* **EPOLLIN**: The associated file is available for **read()** operations
* **EPOLLOUT**: The associated file is available for **write()** operations
* **EPOLLHUP**: Hang up (i.e: close) happened on the associated file descriptor. [epoll_wait()](#epoll_wait) will always wait for this event; it is not necessary to set it in events when calling ``epoll_ctl()``. Check [epoll implementation with FIFO for EPOLLHUP example](#working-with-fifo)
* **EPOLLET**: Edge-triggered event. **EPOLLET won't be returned** in ``struct epoll_event *event`` of ``epoll_wait()``. Check epoll implementation [in FIFO](#working-with-fifo) and [pipe](#working-with-pipe) for EPOLLET.

In constrast to edge-triggered, we have level-triggered. Level-triggered with epoll will have 2 state:

* **State 0**: No data inside the data structure (FIFO, pipe,...)
* **State 1**: Existed data inside the data structure

So if a process (specified by a file descriptor) reads out data from that data structure and not reading all (i.e there is still data left), **state 1** still happens. When all data is read out and no data is left inside that data structure, **state 0** will be triggered. Check [level-triggered epoll in FIFO](Working%20with%20FIFO.md#level-triggered-epoll-in-fifo) for this implementation.

# [Working with terminal](Working%20with%20terminal.md)

* [Working with 1 file descriptor as the current running terminal](Working%20with%20terminal.md#working-with-1-file-descriptor-as-the-current-running-terminal)
* [Working with multiple file descriptors as 2 current running terminals](Working%20with%20terminal.md#working-with-multiple-file-descriptors-as-2-current-running-terminals)

# [Working with FIFO](Working%20with%20FIFO.md)

* [EPOLLHUP and EPOLLET in FIFO](Working%20with%20FIFO.md#epollhup-and-epollet-in-fifo)
* [EPOLLIN in FIFO](Working%20with%20FIFO.md#epollin-in-fifo)
* [Level-triggered epoll in FIFO](Working%20with%20FIFO.md#level-triggered-epoll-in-fifo)
* [Edge-triggered epoll with EPOLLET in FIFO](Working%20with%20FIFO.md#edge-triggered-epoll-with-epollet-in-fifo)

# Working with pipe

## IPC with pipe without EPOLLET

Parent process sends a string to pipe only one time. Child process will read one 1 byte from the pipe. Only **EPOLLIN** event is monitored.

**Program**: [epoll_pipe_without_epollet.c](epoll_pipe_without_epollet.c)

**Result**: 1 byte is read until the whole string inside the pipe is read out

```c
H
e
l
l
o
,
 
W
o
r
l
d
 
!

Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
...
```

## IPC with pipe with EPOLLET

Features like [IPC with pipe without EPOLLET](), but monitor **EPOLLIN** and **EPOLLET**.

**Program**: [epoll_epollet_pipe.c](epoll_epollet_pipe.c)

**Result**: Only 1 byte is read as the status in pipe is change from 0 to having data which is edge trigger. After reading 1 byte, there is still data left inside the pipe so edge trigger event doesn't happen.

```
H
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
```
# Working with character device
* [Response any epoll event from a character device to a userspace process opening it](https://github.com/TranPhucVinh/C/tree/master/Kernel/Character%20device/Character%20device%20operations/Poll#epoll-handling-in-character-device-response-any-events-to-the-userspace-process)
* [Monitor EPOLLIN event for write() system call/cat command](https://github.com/TranPhucVinh/C/tree/master/Kernel/Character%20device/Character%20device%20operations/Poll#epoll-handling-in-character-device-monitor-epollin-event-for-write-system-callcat-command)
* [kmess](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/System%20call/kmess): A program to display kernel log realtime
# Working with TCP and HTTP
* [Single TCP receiver for multiple TCP senders](https://github.com/TranPhucVinh/C/tree/master/Transport%20layer#single-tcp-receiver-for-multiple-tcp-senders-handled-by-epoll)
* [HTTP server for multiple HTTP client]()
# EPOLLET to detect interrupt on GPIO

[With sysfs, use EPOLLET to detect the edge-triggered interrupt on a GPIO in Raspberry Pi](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/blob/main/Physical%20layer/Interrupt.md#detect-the-interrupt-connected-to-a-gpio-for-everytime-there-is-an-edge-triggered).