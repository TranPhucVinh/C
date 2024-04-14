# Working with 1 file descriptor as the current running terminal

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       //Monitor 1 file descriptor as 1 terminal

struct epoll_event monitored_event[MAXEVENTS], happened_event[MAXEVENTS];

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } 
	monitored_event[0].events = EPOLLIN;
	monitored_event[0].data.fd = STDIN_FILENO;//Add file descriptor STDIN_FILENO to monitor

	if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, monitored_event) < 0){
		printf("Unable to add current opening terminal STDIN_FILENO to be monitored by epoll\n");
		return -1;
	}

	while (1){
		int total_ready_fd;// Total ready file descriptors
		total_ready_fd = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
		if (total_ready_fd == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
		else if (total_ready_fd < -1){
            printf("epoll_wait error %d\n", total_ready_fd);        
			close(epfd);
			return -1;
        }
        
        if (total_ready_fd == 1){
			if (happened_event[0].events == EPOLLIN) {
				char buffer[BUFF_SIZE];
				bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
				read(STDIN_FILENO, buffer, sizeof(buffer));
				printf("Entered string: %s\n", buffer);
			}
		}
	}
    return 1;
}
```

**Result**

* If not entering anything to the terminal for ``TIMEOUT`` ms, print out ``Timeout after TIMEOUT miliseconds``
* If entering a string inside ``TIMEOUT`` ms, print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character), print out ``Entered string: 1234567890``

Entering ``1234567890123`` (More than 10 characters), print out: 

``Entered string: 1234567890``

``Entered string: 123``

# Working with multiple file descriptors as 2 current running terminals

Read entered data from the 2 current running terminals:

* Current running program (a.out) on 1st terminal /dev/pts/0
* 2nd terminal is /dev/pts/2

**Program**: [epoll_for_multiple_terminals.c](src/epoll_for_multiple_terminals.c)

**Result**

* If not entering anything to 2 terminals for ``TIMEOUT`` ms, print out ``Timeout after TIMEOUT miliseconds``
* If entering a string inside ``TIMEOUT`` ms on the 1st terminal ``/dev/pts/0`` (running ``a.out``), print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character): Print out ``String from terminal 1: 1234567890``

Entering ``1234567890123`` (More than 10 characters): Print out 

``String from terminal 1: 1234567890``

``String from terminal 1: 123``

* If entering a string inside ``TIMEOUT`` ms on the 2nd terminal ``/dev/pts/2``, print out every character inside that entered string, i.e

Entering ``1234567890`` (10 character), one by one, the character to print out is not continuouslt. E.g:

* ``String from terminal 2: 1``
* ``String from terminal 2: 2``
* ``String from terminal 2: 5`` (3 and 4 are missing)
* ``String from terminal 2: 7`` (6 are missing)
 
That happens as the shell also takes control of this 2nd terminal so the process to enter the input string cause race condition
