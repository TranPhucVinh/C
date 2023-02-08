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
* ``EPOLLET``: Edge-triggered event. ``EPOLLET`` won't be returned in ``struct epoll_event *event`` of ``epoll_wait()``. Check epoll implementation [in FIFO](#working-with-fifo) and [pipe] for EPOLLET.
	      
# [Working with terminal](Working%20with%20terminal.md)

* [Working with 1 file descriptor as the current running terminal](Working%20with%20terminal.md#working-with-1-file-descriptor-as-the-current-running-terminal)
* [Working with multiple file descriptors as 2 current running terminals](Working%20with%20terminal.md#working-with-multiple-file-descriptors-as-2-current-running-terminals)

# Working with FIFO

## EPOLLHUP and EPOLLET in FIFO

Everytime running ``send.c`` will send a string to ``FIFO``, [fifo_epollet.c](fifo_epollet.c) which monitor event ``EPOLLHUP`` (with flag ``EPOLLET`` to make sure the event happen only 1 time exactly as edge trigger) will print out the received string.

**send.c**

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"

int main(int argc, char *argv[])  {
	char writeString[] = "Hello, World !";

	int fd = open(FIFO_NAME, O_WRONLY);
	if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
	else printf("Write to FIFO successfully\n");
	close(fd);
}
```

### Note

``EPOLLHUP`` will be returned continuously on ``fifo_epollet.c`` side right after ``send.c`` successfully sends a string to ``FIFO`` and close its opened ``FIFO`` file descriptor. Without the ``EPOLLET`` flag (edge-triggered), ``EPOLLHUP`` as the same event keeps appearing endlessly.

Program [endlessly_epollhup_event.c](endlessly_epollhup_event.c) will demonstrate this (with ``send.c`` as the sender to FIFO). In ``endlessly_epollhup_event.c``, it only monitors ``EPOLLHUP`` event and has nothing to deal with ``EPOLLET``. Right after the FIFO receives the sent data from ``send.c``, ``EPOLLHUP`` event keeps appearing endlessly. Program ``endlessly_epollhup_event.c`` uses ``count``, a variable to count how many time ``EPOLLHUP`` happens and ``count`` value will increase expressly.

## EPOLLIN FIFO

``send.c`` will send a string to FIFO every 1 second:

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"

int main(int argc, char *argv[])  {
	char writeString[] = "Hello, World !";

	int fd = open(FIFO_NAME, O_WRONLY);
    while (1){
        if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
        else printf("Write to FIFO successfully\n");
        sleep(1);
    }
	close(fd);
}
```

[epollin_fifo.c](epollin_fifo.c) will read the string sent from ``send.c`` to FIFO then print it out, count how many times the string is received (with ``count`` variable), and print out ``Timeout after TIMEOUT miliseconds`` if there is no data sent from ``send.c`` to FIFO. As the string is sent every 1 second for EPOLLIN event will keeps happening.

## epoll level-triggered in FIFO

``send.c`` will send a string to FIFO then enters infinite while loop (in order to keep FIFO opened):

```c
char writeString[] = "Hello, World !";

int fd = open(FIFO_NAME, O_WRONLY);
if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
else printf("Write to FIFO successfully\n");
while(1);
close(fd);
```

``receiver.c`` will have most features like [epollin_fifo.c](epollin_fifo.c), except it only read 1 byte from the FIFO:

```c
//Other parts are like epollin_fifo.c
else if (epollret > 0){
    char buffer[BUFF_SIZE];
    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
    read(fd, buffer, 1);

    if (happened_event[0].events == EPOLLIN) {
        printf("Entered string: %s\n", buffer);
    }
}
```
**Result**:  1 byte is read until the whole string inside the pipe is read out.

```
Open FIFO successfully 4
Entered string: H
Entered string: e
Entered string: l
Entered string: l
Entered string: o
Entered string: ,
Entered string:  
Entered string: W
Entered string: o
Entered string: r
Entered string: l
Entered string: d
Entered string:  
Entered string: !
Entered string: 
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
...
```

## EPOLLET in FIFO

With send.c program like in [epoll level-triggered in FIFO](#epoll-level-triggered-in-fifo), adding ``EPOLLET`` to handle edge-trigger in [epollin_fifo.c](epollin_fifo.c):

```c
//All other part kept like in epollin_fifo.c.c
#define MAXEVENTS   2       //2 event for EPOLLIN and EPOLLET

monitored_event[0].events = EPOLLIN|EPOLLET;

//Other parts are like epollin_fifo.c
else if (epollret > 0){
    char buffer[BUFF_SIZE];
    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
    read(fd, buffer, 1);

    if (happened_event[0].events == EPOLLIN) {
        printf("Entered string: %s\n", buffer);
    }
}
```

**Result**: Only 1 byte is read as the status in pipe is change from 0 to having data which is edge trigger. After reading 1 byte, there is still data left inside the pipe so edge trigger event doesn't happen.

```
Open FIFO successfully 4
Entered string: H
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
...
```

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
