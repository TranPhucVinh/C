#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

#define TIMEOUT     5000    //miliseconds
#define TOTAL_FD    1       //Total number of file descriptors to be monitored

#define BUFF_SIZE   10

struct pollfd fds;

int main(){
    fds.fd = STDIN_FILENO;
    fds.events = 0;
    fds.events |= POLLIN;
    while (1){
        int pret = poll(&fds, TOTAL_FD, TIMEOUT);
       
        if (pret == 0){
            printf("Timeout after %d miliseconds\n", TIMEOUT);
        } else if (pret > 0){
			if (fds.revents == POLLIN) {
				char buffer[BUFF_SIZE];
				bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
				read(STDIN_FILENO, buffer, sizeof(buffer));
				printf("Entered string: %s", buffer);
			}
        } else perror("poll()");
    }
    return 0;
}