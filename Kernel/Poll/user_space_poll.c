#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

#define TIMEOUT     5000 //miliseconds

#define DEVICE_NAME					"/dev/fops_character_device"

struct pollfd fds;

int main(){
    int fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        printf("Unable to open %s\n", DEVICE_NAME);
        return 1;
    };

    int nfds = fd + 1;

    while (1){
        fds.fd = fd;
        fds.events = 0;
        fds.events |= POLLIN;
        int pret = poll(&fds, nfds, TIMEOUT);

        if (pret == 0){
            printf("Timeout after %d miliseconds\n", TIMEOUT);
        } else if (pret == POLLIN){
            printf("POLLIN is responsed from %s\n", DEVICE_NAME);
        }
    }
    return 0;
}