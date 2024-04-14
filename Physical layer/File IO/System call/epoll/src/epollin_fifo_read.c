#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       // Monitor 1 FIFO as 1 file descriptor

#define FIFO        "FIFO"

struct epoll_event monitored_event, happened_event;

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    }

    int fifo_fd = open(FIFO, O_RDONLY|O_NONBLOCK);//Open for write
    if (fifo_fd < 0){
        printf("Unable to open FIFO\n");
    }
    
    printf("Open FIFO successfully %d\n", fifo_fd);
    monitored_event.events = EPOLLIN;
    monitored_event.data.fd = fifo_fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fifo_fd, &monitored_event) < 0){
        printf("Unable to add current opening terminal STDIN_FILENO to be monitored by epoll\n");
        return -1;
    }

    /*
        Variable count will count how many times the event EPOLLIN is triggered
        count value will be increased expressly right after the FIFO receives data
    */
    int count = 0;
    while (1){
        int total_ready_fd = epoll_wait(epfd, &happened_event, MAXEVENTS, TIMEOUT);

        if (total_ready_fd == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
        else if (total_ready_fd < 0){
            printf("epoll_wait error %d\n", total_ready_fd);        
            close(epfd);
            return -1;
        } else {
            char buffer[BUFF_SIZE];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            read(fifo_fd, buffer, sizeof(buffer));

            if (happened_event.events == EPOLLIN) {
                printf("Entered string: %s, %d\n", buffer, count);
                count += 1;
            }
        }
    }
    return 1;
}