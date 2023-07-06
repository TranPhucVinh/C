#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    // miliseconds
#define BUFF_SIZE   50
#define MAXEVENTS   2       // Monitor 2 file descriptors for CHAR_DEV_1 and CHAR_DEV_2

#define CHAR_DEV_1  "/dev/char_dev_1"
#define CHAR_DEV_2  "/dev/char_dev_2"

struct epoll_event monitored_event[MAXEVENTS], happened_event[MAXEVENTS];
char buffer[BUFF_SIZE];

int main(){
    int epfd = epoll_create(EPOLL_CLOEXEC);
    int fd_1 = open(CHAR_DEV_1, O_RDWR);
    if (fd_1 < 0) {
        printf("Unable to open char_dev_1\n");
        return 1;
    }

    int fd_2 = open(CHAR_DEV_2, O_RDWR);
    if (fd_2 < 0) {
        printf("Unable to open char_dev_2\n");
        return 1;
    };

    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } else {
        monitored_event[0].events = EPOLLIN;
        monitored_event[0].data.fd = fd_1;//Add file descriptor fd_1 to monitor
        monitored_event[1].events = EPOLLIN;
        monitored_event[1].data.fd = fd_2;//Add file descriptor fd_2 to monitor

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd_1, &monitored_event[0]) < 0){
            printf("Unable to add terminal 1 to be monitored by epoll\n");
            return 0;
        } 

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd_2, &monitored_event[1]) < 0){
            printf("Unable to add terminal 2 to be monitored by epoll\n");
            return 0;
        } 
    
        while (1){
            int total_ready_fd;// Total ready file descriptors
            total_ready_fd = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
            if (total_ready_fd == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
            else if (total_ready_fd > 0){
                printf("Total ready fd is %d\n", total_ready_fd);
                for (int n = 0; n < total_ready_fd; n++)
                {
                    printf("ready fd: %d\n", happened_event[n].data.fd);
                    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                    if (happened_event[n].data.fd == fd_1) {
                        if (happened_event[n].events == EPOLLIN) {
                            int offset = lseek(fd_1, 0, SEEK_SET);
                            if (!offset){
                                char buffer[BUFF_SIZE];
                                memset(buffer, 0, BUFF_SIZE);
                                read(fd_1, buffer, BUFF_SIZE);
                                printf("String of char_dev_1: %s", buffer);
                            }
                        }
                    }

                    if (happened_event[n].data.fd == fd_2) {
                        if (happened_event[n].events == EPOLLIN) {
                            int offset = lseek(fd_2, 0, SEEK_SET);
                            if (!offset){
                                char buffer[BUFF_SIZE];
                                memset(buffer, 0, BUFF_SIZE);
                                read(fd_2, buffer, BUFF_SIZE);
                                printf("String of char_dev_2: %s", buffer);
                            }
                        }
                    }
                }
            }
            else {
                printf("epoll_wait error %d\n", total_ready_fd);        
                close(epfd);
                return -1;
            }
        }
    }
    return 1;
}
