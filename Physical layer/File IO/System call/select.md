# Working with 1 file descriptor as the current running terminal

Read entered data from the current running terminal

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define TIMEOUT     5 //seconds

#define WRITEFDS    NULL
#define EXCEPTFDS   NULL

#define BUFF_SIZE   10

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
            char buffer[BUFF_SIZE];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            read(STDIN_FILENO, buffer, sizeof(buffer));
            printf("Entered string: %s", buffer);
        }
    }
    return 0;
}
```

**Result**

* If not entering anything to the terminal for ``TIMEOUT`` s, print out ``Timeout after TIMEOUT seconds``
* If entering a string inside ``TIMEOUT`` seconds, print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character), print out ``Entered string: 1234567890``

Entering ``1234567890123`` (More than 10 characters), print out: 

``Entered string: 1234567890``

``Entered string: 123``

# Working with multiple file descriptors as 2 current running terminals

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

#define TERMINAL_1  "/dev/pts/0"
#define TERMINAL_2  "/dev/pts/1"

#define BUFF_SIZE   10

fd_set readfs;

struct timeval timeout;
char buffer[BUFF_SIZE];

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
                    if (fd == ter_1) {
                        bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                        read(fd, buffer, sizeof(buffer));
						printf("String entered in terminal 1: %s", buffer);
                    } else if (fd == ter_2) {
                        bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
                        read(fd, buffer, sizeof(buffer));
						printf("String entered in terminal 2: %s", buffer);
                    }
                }
            }
        }
    }
    return 0;
}
```

**Result**

* If not entering anything to 2 terminals for ``TIMEOUT`` ms, print out ``Timeout after TIMEOUT miliseconds``
* If entering a string inside ``TIMEOUT`` ms on the 1st terminal ``/dev/pts/0`` (running ``a.out``), print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character): Print out ``String from terminal 1: 1234567890``

Entering ``1234567890123`` (More than 10 characters): Print out 

``String from terminal 1: 1234567890``

``String from terminal 1: 123``

* If entering a string inside ``TIMEOUT`` ms on the 2nd terminal ``/dev/pts/1``, all character inside that entered string won't be printed out properly, most of the characters inside that string are printed out one by one separatedly

I.e entering ``1234567890`` (10 character), Print out: 

* ``String from terminal 2: 1``
... Character ``2`` is missed
* ``String from terminal 2: 3``
* ``String from terminal 2: 4``
... Character ``5`` is missed

(Other left characters inside the entered string might be missing)

For better handling with the multiple descriptor monitoring, use [poll()](poll.md) for 2 reasons:

* ``nfds`` argument in ``poll()`` are the total number of ``fd`` to be monitor, not the max ``fd`` being opened in ``select()``
* Better handling of the string entered in the other terminal/file descriptor
