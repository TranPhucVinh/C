The epoll API performs a similar task to ``poll()`` as monitoring multiple file descriptors to see if I/O is possible on any of them. 

# API

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
* ``EPOLLHUP``: Hang up (i.e: close) happened on the associated file descriptor. ``epoll_wait()`` will always wait for this event; it is not necessary to set it in events when calling ``epoll_ctl()``. Check [epoll implementation with FIFO for EPOLLHUP example and level-triggered mode](#working-with-fifo)
* ``EPOLLET``: Edge-triggered event.  Check [epoll implementation with FIFO for edge-triggered event handler along with EPOLLHUP event](#working-with-fifo)
	      
# Implementations

## Working with terminal

* [Working with 1 file descriptor as the current running terminal](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/epoll/Implementations.md#working-with-1-file-descriptor-as-the-current-running-terminal)
* [Working with multiple file descriptors as 2 current running terminals](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/epoll/Implementations.md#working-with-multiple-file-descriptors-as-2-current-running-terminals)

## Working with FIFO

Everytime ``send.c`` sends a string to ``FIFO``, ``receive.c`` which monitor event ``EPOLLHUP`` (with flag ``EPOLLET`` to make sure the event happen only 1 time exactly as edge trigger) will print out the receive string.

### send.c

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

### receive.c

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       //1 event for EPOLLIN

#define FIFO        "FIFO"

struct epoll_event monitored_event[1], happened_event[1];

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } else {
        int fd = open(FIFO, O_RDONLY|O_NONBLOCK);//Open for write
        if (fd > 0){
            printf("Open FIFO successfully %d\n", fd);
            monitored_event[0].events = EPOLLET;

            monitored_event[0].data.fd = fd;

            if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, monitored_event) < 0){
                printf("Unable to add current opening terminal STDIN_FILENO to be monitored by epoll\n");
                return 0;
            } else {
                while (1){
                    int epollret = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
                    if (epollret == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
                    else if (epollret > 0){
                        char buffer[BUFF_SIZE];
                        bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                        read(fd, buffer, sizeof(buffer));

                        /*
                            If checking event with EPOLLET like this: if (happened_event[0].events == EPOLLET)
                            this condition will never happen

                            As epoll_wait() will always wait for EPOLLHUP, it is not necessary to set EPOLLHUP in events
                            when calling epoll_ctl() as well as don't need to monitor by if else like this:
                            if (happened_event[0].events == EPOLLHUP) printf("Entered string: %s\n", buffer);
                        */                         
                        printf("Entered string: %s\n", buffer);
                    }
                    else {
                        printf("epoll_wait error %d\n", epollret);        
                        close(epfd);
                        return -1;
                    }
                }
            }
        } else printf("Unable to open %s with fd %d\n", FIFO, fd);
    }
    return 1;
}
```
### Note

``EPOLLHUP`` will be returned continuously on ``receive.c`` side right after [send.c](#sendc) successfully sends a string to ``FIFO`` and close its opened ``FIFO`` file descriptor. Without the ``EPOLLET`` flag (edge-triggered), ``EPOLLHUP`` as the same event keeps appearing endlessly, this is known as **level-trigger mode**. 

Also note that with ``send.c`` program above, if the string sending process is blocking inside the while loop like this, ``EPOLLHUP`` event won't be caught in ``receive.c`` until ``send.c`` is stopped so that its ``FIFO`` file descriptor is closed:

```c
//Sending string to FIFO inisde while loop like this in send.c will stop EPOLLHUP event to be caught by receive.c
while (1){
        if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
    	else printf("Write to FIFO successfully\n");
        sleep(1);
}
```    

Program [endlessly_epollhup_event.c](endlessly_epollhup_event.c) will demonstrate this (with ``send.c`` as the sender to FIFO). In ``endlessly_epollhup_event.c``, it only monitors ``EPOLLHUP`` event and has nothing to deal with ``EPOLLET``. Right after the FIFO receives the sent data from ``send.c``, ``EPOLLHUP`` event keeps appearing endlessly. Program ``endlessly_epollhup_event.c`` uses ``count``, a variable to count how many time ``EPOLLHUP`` happens and ``count`` value will increase expressly.
