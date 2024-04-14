# EPOLLHUP and EPOLLET in FIFO

**Features**: Everytime running [send.c](#send.c) will send a string to ``FIFO``, [epollet_fifo.c](src/epollet_fifo.c) which monitor event type **EPOLLHUP** (with event type **EPOLLET** to make sure the event happen only 1 time exactly as edge trigger) will print out the received string.

**Create FIFO**: ``mkfifo -m 777 FIFO``

## send.c

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

## Note

``EPOLLHUP`` will be returned continuously on [epollet_fifo.c](src/epollet_fifo.c) side right after ``send.c`` successfully sends a string to ``FIFO`` and close its opened ``FIFO`` file descriptor. Without the ``EPOLLET`` flag (edge-triggered), ``EPOLLHUP`` as the same event keeps appearing endlessly.

Program [endlessly_epollhup_event.c](src/endlessly_epollhup_event.c) will demonstrate this (with ``send.c`` as the sender to FIFO). In ``endlessly_epollhup_event.c``, it only monitors ``EPOLLHUP`` event and has nothing to deal with ``EPOLLET``. Right after the FIFO receives the sent data from ``send.c``, ``EPOLLHUP`` event keeps appearing endlessly. Program ``endlessly_epollhup_event.c`` uses ``count``, a variable to count how many time ``EPOLLHUP`` happens and ``count`` value will increase expressly.

# EPOLLIN in FIFO

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

[epollin_fifo.c](src/epollin_fifo.c) will read the string in FIFO, which is sent from ``send.c``, then print it out, count how many times the string is received (with ``count`` variable), and print out ``Timeout after TIMEOUT miliseconds`` if there is no data sent from ``send.c`` to FIFO. The string is sent every 1 second for EPOLLIN event will keeps happening.

# Level-triggered epoll in FIFO

**send.c** will send a string to FIFO then enters infinite while loop (in order to keep FIFO opened):

```c
char writeString[] = "Hello, World !";

int fd = open(FIFO_NAME, O_WRONLY);
if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
else printf("Write to FIFO successfully\n");
while(1);
close(fd);
```

**receiver.c** will have most features like [epollin_fifo.c](src/epollin_fifo.c), except it only reads 1 byte from the FIFO to keep level-triggered event:

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
**Result**: 1 byte is read until the whole string inside the FIFO is read out.

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
# Edge-triggered epoll with EPOLLET in FIFO

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

**Result**: Only 1 byte is read as the status in FIFO is change from 0 to having data which is **edge trigger**. After reading 1 byte, there is still data left inside the FIFO so edge trigger event doesn't happen.

```
Open FIFO successfully 4
Entered string: H
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
...
```
