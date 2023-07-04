#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   50
#define MAXEVENTS   1       //Only 1 event EPOLLIN

#define DEVICE_NAME	"/dev/fops_character_device"

struct epoll_event monitored_event[1], happened_event[1];

int main(){
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    int fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        printf("Unable to open %s\n", DEVICE_NAME);
        return 1;
    };

    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } else {
        monitored_event[0].events = 0;
        monitored_event[0].events |= EPOLLIN;// read()
        monitored_event[0].data.fd = fd;//Add file descriptor of DEVICE_NAME to monitor

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &monitored_event[0]) < 0){
            printf("Unable to add %s terminal 1 to be monitored by epoll\n", DEVICE_NAME);
            return 0;
        } else {    
            while (1){
                int total_ready_fd;// Total ready file descriptors
                total_ready_fd = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
                if (total_ready_fd == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
                else if (total_ready_fd == 1){
                    if (happened_event[0].data.fd == fd){
                        if (happened_event[0].events == EPOLLIN) {
                            int offset = lseek(fd, 0, SEEK_SET);
                            if (!offset){
                                char buffer[BUFF_SIZE];
                                memset(buffer, 0, BUFF_SIZE);
                                read(fd, buffer, BUFF_SIZE);
                                printf("EPOLLIN event: %s", buffer);
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
    }
    return 1;
}