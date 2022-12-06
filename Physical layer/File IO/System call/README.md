# Fundamental concepts

Four key system calls for performing file manipulations:

```c
fd = open(pathname, flags, mode);//defined in fcntl.h
```
```c
numread = read(fd, buffer, count);//defined in unistd.h
```
```c
numwritten = write(fd, buffer, count);//defined in unistd.h
```
```c
status = close(fd);//defined in unistd.h
```

**File descriptor**: The I/O system calls refer to open files using a file descriptor, a (usually small) non-negative integer. A file descriptor is typically obtained by a call to ``open()``, which takes a pathname argument specifying a file upon which I/O is to be performed.

Normally, a process inherits three open file descriptors when it is started by the shell (defined in ``stdio.h`` on Windows and in ``unistd.h`` on Unix)

```c
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```

## Header files

* ``fcntl.h``: file control options
* ``unistd.h`` provides access to the POSIX OS API.

# API

* [fcntl.h header files API](fcntl.md)
* [unistd.h header files API](unistd.md)

## termios.h

```c
#include <termios.h>

int tcgetattr(int fildes, struct termios *termios_p);
```

``tcsetattr``: set the parameters associated with the terminal

```c
#include <termios.h>

int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);
```

The ``tcsetattr()`` function shall set the parameters associated with the terminal referred to by the open file descriptor ``fildes`` (an open file descriptor associated with a terminal) from the ``termios`` structure referenced by ``termios_p`` as follows:

* If ``optional_actions`` is ``TCSANOW``, the change shall occur immediately.
* If ``optional_actions`` is ``TCSADRAIN``, the change shall occur after all output written to ``fildes`` is transmitted. This function should be used when changing parameters that affect output.
* If ``optional_actions`` is ``TCSAFLUSH``, the change shall occur after all output written to ``fildes`` is transmitted, and all input so far received but not read shall be discarded before the change is made.

## I/O multiplexing API

### select()

``select()`` allows a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation (e.g., input possible).

```c
#include <sys/time.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
```

* ``nfds``: **This is not the total number of file descriptor that need to be monitor**. ``nfds`` must have the value of the highest opened ``fd`` value + 1. E.g, if ``12`` is the highest value of the opened ``fd``, then ``nfds`` is ``13``. So, if you want to monitor file descriptors ``24``-``31``, you'd set nfds to ``32``
The ``timeout`` argument specifies the interval that ``select()`` should block waiting for a file descriptor to become ready. The call will block until either:
*  a file descriptor becomes ready;
*  the call is interrupted by a signal handler
*  the timeout expires

Four macros are provided to manipulate the sets. ``FD_ZERO()`` clears a set. ``FD_SET()`` and ``FD_CLR()`` respectively add and remove a given file descriptor from a set. ``FD_ISSET()`` tests to see if a file descriptor is part of the set; this is useful after ``select()`` returns.

### poll()

``poll()`` performs a similar task to ``select()``, it waits for one of a set of file descriptors to become ready to perform I/O

```c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

```c
struct pollfd {
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```

``nfds_t``: An unsigned integer type used for the number of file descriptors.

**Parameters**

* ``nfds``: Total number of file descriptors to monitor by ``poll()``
* ``events``: A bit mask specifying the events the application is interested in for the file descriptor ``fd``. It is an input parametr (i.e setup in program)

    * ``POLLIN``: There is data to read.
    * ``POLLOUT``: Writing is now possible

* ``revents``:  The bits returned in ``revents`` can include any of those specified in ``events``, or one of the values ``POLLERR``, ``POLLHUP``, or ``POLLNVAL``. It is an output parameter, i.e return in function ``poll()``

**Return**:  

* On success, a positive number is returned; this is the number of structures which have nonzero ``revents`` fields
* ``0``: Call timed out and no file descriptors were ready.
* ``-1``: Error

### epoll

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
The ``epoll_wait()`` system call waits for events on the ``epoll()`` instance referred to by the file descriptor ``epfd``.

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

# Examples

* [File operations](File%20operations.md)
* [Device file operations](Device%20file%20operations.md)
* [I/O multiplexing](IO%20multiplexing.md)
