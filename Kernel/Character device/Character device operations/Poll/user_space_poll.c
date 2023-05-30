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
    fds.fd = fd;
    fds.events = 0;
    fds.events |= POLLPRI;// open()
    fds.events |= POLLIN;// read()
    fds.events |= POLLOUT;// write()
    fds.events |= POLLHUP;// close()

    if (fd < 0) {
        printf("Unable to open %s\n", DEVICE_NAME);
        return 1;
    } else {
        printf("Open %s successfully\n", DEVICE_NAME);
        int nfds = fd + 1;

        while (1){
            int pret = poll(&fds, nfds, TIMEOUT);

            if (pret == 0){
                printf("Timeout after %d miliseconds\n", TIMEOUT);
            } else if (pret > 0) {
                switch (fds.revents){
                    case POLLIN:
                    {
                        printf("read() to get POLLIN from %s\n", DEVICE_NAME);
                        break;
                    } 
                    case POLLPRI:
                    {
                        printf("open() to get POLLPRI from %s\n", DEVICE_NAME);
                        break;
                    }
                    case POLLOUT:
                    {
                        printf("write() to get POLLOUT from %s\n", DEVICE_NAME);
                        break;
                    }
                    case POLLHUP:
                    {
                        printf("close() to get POLLHUP from %s\n", DEVICE_NAME);
                        break;
                    }
                    default:
                    {
                        printf("Unhandled poll event from %s\n", DEVICE_NAME);
                        break;
                    }
                }
            } else {
                perror("poll()");
            }
        }
        return 0;
    }
}