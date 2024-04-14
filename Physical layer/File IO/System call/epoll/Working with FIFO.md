# EPOLLHUP and EPOLLET in FIFO

**Features**: Everytime running [epollet_fifo_write.c](#epollet_fifo_write.c) will send a string to ``FIFO``, [epollet_fifo_read.c](src/epollet_fifo_read.c) which monitors event type **EPOLLHUP** (with event type **EPOLLET** to make sure the event happens only 1 time exactly as edge trigger) will print out the received string.

**Create FIFO**: ``mkfifo -m 777 FIFO``

## epollet_fifo_write.c

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

## Result

```
username@hostname:~/work-in-progress$ ./epollet_fifo_read
Open FIFO successfully 4
String read from FIFO: Hello, Wor
Timeout after 5000 miliseconds
String read from FIFO: ld !
Timeout after 5000 miliseconds
String read from FIFO: 
...
```
## Note

**EPOLLHUP** will be returned continuously on [epollet_fifo_read.c](src/epollet_fifo_read.c) side right after ``epollet_fifo_write.c`` successfully sends a string to ``FIFO`` and close its opened ``FIFO`` file descriptor. Without the ``EPOLLET`` flag (edge-triggered), **EPOLLHUP** as the same event keeps appearing endlessly.

Program [endlessly_epollhup_event.c](src/endlessly_epollhup_event.c) will demonstrate this (with ``epollet_fifo_write.c`` as the sender to FIFO). In ``endlessly_epollhup_event.c``, it only monitors ``EPOLLHUP`` event and has nothing to deal with ``EPOLLET``. Right after the FIFO receives the sent data from ``epollet_fifo_write.c``, ``EPOLLHUP`` event keeps appearing endlessly. Program ``endlessly_epollhup_event.c`` uses ``count``, a variable to count how many time ``EPOLLHUP`` happens and ``count`` value will increase expressly.

# EPOLLIN in FIFO

**epollin_fifo_write.c** will send a string to FIFO every 1 second:

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

[epollin_fifo_read.c](src/epollin_fifo_read.c) will read the string in FIFO, which is sent from ``epollin_fifo_write.c``, then print it out, count how many times the string is received (with ``count`` variable), and print out ``Timeout after TIMEOUT miliseconds`` if there is no data sent from ``epollin_fifo_write.c`` to FIFO. The string is sent every 1 second for EPOLLIN event will keeps happening.

**Result**
```
Open FIFO successfully 4
Entered string: Hello, Wor, 0
Entered string: ld !, 1
Entered string: Hello, Wor, 2
Entered string: ld !, 3
...
```
# Level-triggered epoll in FIFO

**epollet_fifo_write.c** will send a string to FIFO then enters infinite while loop (in order to keep FIFO opened):

```c
char writeString[] = "Hello, World !";

int fd = open(FIFO_NAME, O_WRONLY);
if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
else printf("Write to FIFO successfully\n");
while(1);
close(fd);
```

**epollet_fifo_read.c** will have most features like [epollin_fifo_read.c](src/epollin_fifo_read.c), except it only reads 1 byte from the FIFO to keep level-triggered event:

```c
//Other parts are like epollin_fifo_read.c
char buffer[BUFF_SIZE];
bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
read(fifo_fd, buffer, 1);

if (happened_event.events == EPOLLIN) {
    printf("Entered string: %s, %d\n", buffer, count);
}
```
**Result**: 1 byte is read until the whole string inside the FIFO is read out.

```
Open FIFO successfully 4
Read from buffer: H
Read from buffer: e
Read from buffer: l
Read from buffer: l
Read from buffer: o
Read from buffer: ,
Read from buffer:  
Read from buffer: W
Read from buffer: o
Read from buffer: r
Read from buffer: l
Read from buffer: d
Read from buffer:  
Read from buffer: !
Read from buffer: 
Timeout after 5000 miliseconds
Timeout after 5000 miliseconds
...
```
# Edge-triggered epoll with EPOLLET in FIFO

With **epollet_fifo_write.c** program like in [epoll level-triggered in FIFO](#level-triggered-epoll-in-fifo), adding ``EPOLLET`` to handle edge-trigger in [epollin_fifo_read.c](src/epollin_fifo_read.c):

```c
//All other part kept like in epollin_fifo_read.c.c
#define MAXEVENTS   2       //2 event for EPOLLIN and EPOLLET

monitored_event[0].events = EPOLLIN|EPOLLET;

//Other parts are like epollin_fifo_read.c
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
