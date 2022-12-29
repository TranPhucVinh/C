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