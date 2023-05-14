# Working with 1 file descriptor as the current running terminal

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       //1 event for EPOLLIN

struct epoll_event monitored_event[1], happened_event[1];

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } else {
        monitored_event[0].events = EPOLLIN;
        monitored_event[0].data.fd = STDIN_FILENO;//Add file descriptor STDIN_FILENO to monitor

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, monitored_event) < 0){
            printf("Unable to add current opening terminal STDIN_FILENO to be monitored by epoll\n");
            return 0;
        } else {
            while (1){
                int epollret = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
                if (epollret == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
                else if (epollret > 0){
                    char buffer[BUFF_SIZE];
                    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                    read(STDIN_FILENO, buffer, sizeof(buffer));
                    if (happened_event[0].events == EPOLLIN) printf("Entered string: %s", buffer);
                }
                else {
                    printf("epoll_wait error %d\n", epollret);        
                    close(epfd);
                    return -1;
                }
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

* Current running program (a.out) on 1st terminal /dev/pts/4
* 2nd terminal is /dev/pts/18

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       //Only 1 event EPOLLIN for 2 file descriptors

#define TERMINAL_1  "/dev/pts/4"
#define TERMINAL_2  "/dev/pts/18"

struct epoll_event monitored_event[2], happened_event[1];
char buffer[BUFF_SIZE];

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    int ter_1 = open(TERMINAL_1, O_RDWR);
    if (ter_1 < 0) {
        printf("Unable to open terminal 1\n");
        return 1;
    };

    int ter_2 = open(TERMINAL_2, O_RDWR);
    if (ter_2 < 0) {
        printf("Unable to open terminal 2\n");
        return 1;
    };

    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } else {
        monitored_event[0].events = EPOLLIN;
        monitored_event[0].data.fd = ter_1;//Add file descriptor ter_1 to monitor
        monitored_event[1].events = EPOLLIN;
        monitored_event[1].data.fd = ter_2;//Add file descriptor ter_2 to monitor

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, ter_1, &monitored_event[0]) < 0){
            printf("Unable to add terminal 1 to be monitored by epoll\n");
            return 0;
        } 

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, ter_2, &monitored_event[1]) < 0){
            printf("Unable to add terminal 2 to be monitored by epoll\n");
            return 0;
        } 
    
        while (1){
            int epollret = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
            if (epollret == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
            else if (epollret > 0){
                //As struct epoll_event monitored_event[2] and happened_event[1] are different
                //so use for loop to check
                for (int n = 0; n < 2; n++)
                {
                    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                    if (happened_event[n].data.fd == ter_1) {
                        read(ter_1, buffer, sizeof(buffer));                    
                        printf("String from terminal 1: %s\n", buffer);
                    }

                    if (happened_event[n].data.fd == ter_2) {
                        read(ter_2, buffer, sizeof(buffer));                    
                        printf("String from terminal 2: %s\n", buffer);
                    }                
                }
            }
            else {
                printf("epoll_wait error %d\n", epollret);        
                close(epfd);
                return -1;
            }
        }
    }
    return 1;
}
```

**Result**

* If not entering anything to 2 terminals for ``TIMEOUT`` ms, print out ``Timeout after TIMEOUT miliseconds``
* If entering a string inside ``TIMEOUT`` ms on the 1st terminal ``/dev/pts/4`` (running ``a.out``), print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character): Print out ``String from terminal 1: 1234567890``

Entering ``1234567890123`` (More than 10 characters): Print out 

``String from terminal 1: 1234567890``

``String from terminal 1: 123``

* If entering a string inside ``TIMEOUT`` ms on the 2nd terminal ``/dev/pts/18``, print out that entered string by the chunk of ``BUFF_SIZE`` (like the behavior in 1st terminal)
