#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>//for bzero()
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   2       //Monitor 2 terminals/file descriptors

#define TERMINAL_1  "/dev/pts/0"
#define TERMINAL_2  "/dev/pts/2"

struct epoll_event monitored_event[MAXEVENTS], happened_event[MAXEVENTS];

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
            int total_ready_fd;// Total ready file descriptors
            total_ready_fd = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
            if (total_ready_fd == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
            else if (total_ready_fd > 0){
                // It's impossible to enter input data to 2 terminals at the same time so 
                // Total ready fd is always 1.
                printf("Total ready fd is %d\n", total_ready_fd);

                //The increment condition will be total_ready_fd+1 for index [0] [1]
                for (int i = 0; i < total_ready_fd+1; i++)
                {
                    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                    
                    if ((happened_event[i].data.fd == ter_1)) {
                        if (happened_event[i].events == EPOLLIN){
                            read(ter_1, buffer, sizeof(buffer));                    
                            printf("String from terminal 1: %s\n", buffer);
                        }
                    }
                    if (happened_event[i].data.fd == ter_2) {
                        if (happened_event[i].events == EPOLLIN){
                            read(ter_2, buffer, sizeof(buffer));                    
                            printf("String from terminal 2: %s\n", buffer);
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