## Example 1

Working with 1 file descriptor using ``select()``

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define TOTAL_FD    1 
#define TIMEOUT     5 //seconds

#define WRITEFDS    NULL
#define EXCEPTFDS   NULL

fd_set readfs;

struct timeval timeout;

int main(){
    while (1){
        timeout.tv_sec = TIMEOUT;//Must set time out every time in the while loop
        FD_SET(STDIN_FILENO, &readfs);

        int sret = select(TOTAL_FD, &readfs, WRITEFDS, EXCEPTFDS, &timeout);

        if (sret == 0){
            printf("Timeout after %d seconds\n", TIMEOUT);
        } else {
            char buffer[10];
            bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
            read(STDIN_FILENO, buffer, sizeof(buffer));
            write(STDOUT_FILENO, buffer, sizeof(buffer));
        }
    }
    return 0;
}
```