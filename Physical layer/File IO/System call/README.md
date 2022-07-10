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

Normally, a process inherits three open file descriptors when it is started by the shell:

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

## Other API

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

``poll()`` performs a similar task to select``()``, it waits for one of a set of file descriptors to become ready to perform I/O

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
**Parameters**

* ``events``: A bit mask specifying the events the application is interested in for the file descriptor ``fd``. It is an input parametr (i.e setup in program)

    * ``POLLIN``: There is data to read.
    * ``POLLOUT``: Writing is now possible

* ``revents``:  The bits returned in ``revents`` can include any of those specified in ``events``, or one of the values ``POLLERR``, ``POLLHUP``, or ``POLLNVAL``. It is an output parameter, i.e return in function ``poll()``

**Return**:  

* On success, a positive number is returned; this is the number of structures which have nonzero ``revents`` fields
* ``0``: Call timed out and no file descriptors were ready.
* ``-1``: Error

# Examples

[File descriptor examples](File%20descriptor%20examples.md)

[I/O multiplexing examples](IO%20multiplexing%20examples.md)