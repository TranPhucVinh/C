The epoll API performs a similar task to ``poll()`` as monitoring multiple file descriptors to see if I/O is possible on any of them. 

# API

## Two lists

The central concept of the ``epoll`` API is the epoll instance, an in-kernel data structure which, from a user-space perspective, can be considered as a container for two lists:

* The **interest** list (sometimes also called the **epoll set**): the set of file descriptors that the process has registered an interest in monitoring.

* The **ready** list: the set of file descriptors that are "ready" for I/O.

## epoll_create()

```c
#include <sys/epoll.h>
int epoll_create(int size);
int epoll_create1(int flags);
```

``epoll_create1()`` is the same as ``epoll_create()`` as they create a new ``epoll()`` instance. ``epoll_create()`` returns a file descriptor ``efd`` referring to the new ``epoll`` instance.

* ``flags``: This argument takes only 1 value ``EPOLL_CLOEXEC`` as set the close-on-exec flag on the new file descriptor.

## epoll_wait()

```c
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```
The ``epoll_wait()`` system call waits for events on the ``epoll()`` instance referred to by the file descriptor ``epfd``. On success, ``epoll_wait()`` returns the number of file descriptors ready for the requested I/O, or zero if no file descriptor became ready during the requested ``timeout`` milliseconds.

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

The ``events`` member of the ``epoll_event`` structure is a bit mask composed by ORing together zero or more of the available event types like ``EPOLLIN``, ``EPOLLOUT``,...

* ``EPOLLIN``: The associated file is available for ``read()`` operations
* ``EPOLLOUT``: The associated file is available for ``write()`` operations
* ``EPOLLHUP``: Hang up (i.e: close) happened on the associated file descriptor. ``epoll_wait()`` will alway wait for this event; it is not necessary to set it in events when calling ``epoll_ctl()``. Check [epoll implementation with FIFO for EPOLLHUP example](#working-with-fifo)
* ``EPOLLET``: Edge-triggered event. ``EPOLLET`` won't be returned in ``struct epoll_event *event`` of ``epoll_wait()``. Check epoll implementation [in FIFO](#working-with-fifo) and [pipe](#working-with-pipe) for EPOLLET.
	      
# [Working with terminal](Working%20with%20terminal.md)

* [Working with 1 file descriptor as the current running terminal](Working%20with%20terminal.md#working-with-1-file-descriptor-as-the-current-running-terminal)
* [Working with multiple file descriptors as 2 current running terminals](Working%20with%20terminal.md#working-with-multiple-file-descriptors-as-2-current-running-terminals)

# Working with FIFO

* [EPOLLHUP and EPOLLET in FIFO]()
* [EPOLLIN in FIFO]()
* [Level-triggered epoll in FIFO]()
* [Edge-triggered epoll with EPOLLET in FIFO]()

# Working with pipe

## IPC with pipe without EPOLLET

Parent process sends a string to pipe only one time. Child process will read one 1 byte from the pipe. Only EPOLLIN event is monitor.

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

Features lilke [IPC with pipe without EPOLLET](), but monitor EPOLLIN and EPOLLET

**Program**: [epoll_epollet_pipe.c](epoll_epollet_pipe.c)

**Result**: Only 1 byte is read as the status in pipe is change from 0 to having data which is edge trigger. After reading 1 byte, there is still data left inside the pipe so edge trigger event doesn't happen.

```
H
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
```
