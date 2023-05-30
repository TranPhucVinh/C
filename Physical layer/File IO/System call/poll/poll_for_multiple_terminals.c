#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

#define TIMEOUT     5000 //miliseconds

#define TERMINAL_1  "/dev/pts/1"
#define TERMINAL_2  "/dev/pts/2"

#define TOTAL_FD    2       //Total number of file descriptors to be monitored
#define BUFF_SIZE   10

struct pollfd fds[2];

int main(){
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

    fds[0].fd = ter_1;//Add file descriptor ter_1 to monitor
    fds[0].events = 0;//Init fds[0].events
    fds[0].events |= POLLIN;

    fds[1].fd = ter_2;//Add file descriptor ter_2 to monitor
    fds[1].events = 0;//Init fds[1].events
    fds[1].events |= POLLIN;

    while (1){
        int pret = poll(fds, TOTAL_FD, TIMEOUT);

        if (pret == 0){
            printf("Timeout after %d miliseconds\n", TIMEOUT);
        } else if (pret > 0){
            char buffer[BUFF_SIZE];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            if (fds[0].revents == POLLIN) {
                read(fds[0].fd, buffer, sizeof(buffer));
                printf("String from terminal 1: %s\n", buffer);
            }
            if (fds[1].revents == POLLIN) {
                read(fds[1].fd, buffer, sizeof(buffer));
                printf("String from terminal 2: %s", buffer);
            }
        } else perror("poll()");
    }
    return 0;
}