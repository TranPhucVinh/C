## select() example

Working with 1 file descriptor using ``select()``: Read entered data from the current running terminal

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define TIMEOUT     5 //seconds

#define WRITEFDS    NULL
#define EXCEPTFDS   NULL

fd_set readfs;

struct timeval timeout;

int main(){
    int nfds = STDIN_FILENO + 1;

    while (1){
        timeout.tv_sec = TIMEOUT;//Must set time out every time in the while loop
        FD_SET(STDIN_FILENO, &readfs);//Must be inside while() loop to handle in every loop

        int sret = select(nfds, &readfs, WRITEFDS, EXCEPTFDS, &timeout);

        if (sret == 0){
            printf("Timeout after %d seconds\n", TIMEOUT);
        } else {
            char buffer[10];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            read(STDIN_FILENO, buffer, sizeof(buffer));
            printf("%s", buffer);
        }
    }
    return 0;
}
```

Read entered data from the 2 current running terminals:

* Current running program (``a.out``) on terminal ``/dev/pts/2``
* 2nd terminal is ``/dev/pts/18``

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define TIMEOUT     5 //seconds

#define WRITEFDS    NULL
#define EXCEPTFDS   NULL

#define TERMINAL_1  "/dev/pts/18"
#define TERMINAL_2  "/dev/pts/2"

fd_set readfs;

struct timeval timeout;

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

    int nfds = ter_2 + 1;

    while (1){
        timeout.tv_sec = TIMEOUT;//Must set time out every time in the while loop

        FD_ZERO(&readfs);//Might not need this one
        FD_SET(ter_1, &readfs);
        FD_SET(ter_2, &readfs);
        
        int sret = select(nfds, &readfs, WRITEFDS, EXCEPTFDS, &timeout);

        if (sret == 0){
            printf("Timeout after %d seconds\n", TIMEOUT);
        } else {
            for (int fd = 0; fd <= nfds; fd++) {
                if (FD_ISSET(fd, &readfs)) {
                    if ((fd == ter_1) || (fd == ter_2)) {
                        char buffer[10];
                        bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                        read(fd, buffer, sizeof(buffer));
						printf("%s", buffer);
                    }
                }
            }
        }
    }
    return 0;
}
```

To enter string in the 2nd terminal, simply enter them on the texting area, i.e:

```sh
username$hostname: Enter the string here for /dev/pts/18
```

Send the string by ``echo`` (``echo Hello > /dev/pts/18``) will not work.

## poll() example

Working with 1 file descriptor using ``poll()``: Read entered data from the current running terminal

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

#define TIMEOUT     5000 //miliseconds

struct pollfd fds;

int main(){
    int nfds = STDIN_FILENO + 1;

    while (1){
        fds.fd = STDIN_FILENO;
        fds.events = 0;
        fds.events |= POLLIN;

        int pret = poll(&fds, nfds, TIMEOUT);
       
        if (pret == 0){
            printf("Timeout after %d miliseconds\n", TIMEOUT);
        } else if (pret == POLLIN){
            char buffer[10];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            read(STDIN_FILENO, buffer, sizeof(buffer));
            printf("%s", buffer);
        }
    }
    return 0;
}
```

Read entered data from the 2 current running terminals (All operations are identical to the corresponded example in ``select()``):

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

#define TIMEOUT     5000 //miliseconds

#define TERMINAL_1  "/dev/pts/18"
#define TERMINAL_2  "/dev/pts/4"

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

    int nfds = ter_2 + 1;

    while (1){
        fds[0].fd = ter_1;
        fds[0].events = 0;
        fds[0].events |= POLLIN;

        fds[1].fd = ter_2;
        fds[1].events = 0;
        fds[1].events |= POLLIN;

        int pret = poll(fds, nfds, TIMEOUT);

        if (pret == 0){
            printf("Timeout after %d miliseconds\n", TIMEOUT);
        } else if (pret == POLLIN){
            char buffer[10];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            if (fds[0].revents == POLLIN) read(fds[0].fd, buffer, sizeof(buffer));
            if (fds[1].revents == POLLIN) read(fds[1].fd, buffer, sizeof(buffer));
            printf("%s", buffer);
        }
    }
    return 0;
}
```