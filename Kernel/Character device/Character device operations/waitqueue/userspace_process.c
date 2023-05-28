#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define DEV_NAME "/dev/fops_character_device"

int fd;

int main(){
    printf("PID %d\n", getpid());
    fd = open(DEV_NAME, O_RDWR);
    if(fd < 0) {
        printf("Fail to open %s\n",DEV_NAME);
        return 1;
    } else {
        int a;
        printf("Open %s successfully\n", DEV_NAME);
        read(fd, &a, 1);
        printf("read() successfully\n");
        return 0;
    }
}
