The epoll API performs a similar task to ``poll()`` as monitoring multiple file descriptors to see if I/O is possible on any of them. 

The central concept of the ``epoll`` API is the epoll instance, an in-kernel data structure which, from a user-space perspective, can be considered as a container for two lists:

* The **interest** list (sometimes also called the **epoll set**): the set of file descriptors that the process has registered an interest in monitoring.

* The **ready** list: the set of file descriptors that are "ready" for I/O.

```c
#include <sys/epoll.h>
int epoll_create(int size);
int epoll_create1(int flags);
```

``epoll_create1()`` is the same as ``epoll_create()`` as they create a new ``epoll()`` instance. ``epoll_create()`` returns a file descriptor ``efd`` referring to the new ``epoll`` instance.

* ``flags``: This argument takes only 1 value ``EPOLL_CLOEXEC`` as set the close-on-exec flag on the new file descriptor.

```c
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```
The ``epoll_wait()`` system call waits for events on the ``epoll()`` instance referred to by the file descriptor ``epfd``. On success, ``epoll_wait()`` returns the number of file descriptors ready for the requested I/O, or zero if no file descriptor became ready during the requested ``timeout`` milliseconds.

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

``epoll_ctl()`` system call is used to add, modify, or remove entries in **the interest list** of the ``epoll()`` instance referred to by the file descriptor ``epfd``.

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
