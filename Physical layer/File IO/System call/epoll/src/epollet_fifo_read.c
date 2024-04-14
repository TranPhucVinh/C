#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    // miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       // Monitor 1 FIFO as 1 file descriptor

#define FIFO        "FIFO"

struct epoll_event monitored_event, happened_event;

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return -1;
    }

    int fifo_fd = open(FIFO, O_RDONLY|O_NONBLOCK);//Open for write
    if (fifo_fd < 0){
        printf("Unable to open FIFO\n");
        return -1;
    }
    
    printf("Open FIFO successfully %d\n", fifo_fd);
    monitored_event.events = EPOLLET;
    monitored_event.data.fd = fifo_fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fifo_fd, &monitored_event) < 0){
        printf("Unable to add FIFO to be monitored by epoll\n");
        return 0;
    }

    while (1){
        int epollret = epoll_wait(epfd, &happened_event, MAXEVENTS, TIMEOUT);
        if (epollret == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
        else if (epollret < 0){
            printf("epoll_wait error %d\n", epollret);        
            close(epfd);
            return -1;
        }

        char buffer[BUFF_SIZE];
        bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
        read(fifo_fd, buffer, sizeof(buffer));

        /*
            If checking event with EPOLLET like this: if (happened_event[0].events == EPOLLET)
            this condition will never happen

            As epoll_wait() will always wait for EPOLLHUP, it is not necessary to set EPOLLHUP 
            in monitored_event[0].events when calling epoll_ctl() as well as don't need to monitor
            by if else like this:
            if (happened_event[0].events == EPOLLHUP) printf("String read from FIFO: %s\n", buffer);
        */                         
        printf("String read from FIFO: %s\n", buffer);
    }
    return 1;
}
