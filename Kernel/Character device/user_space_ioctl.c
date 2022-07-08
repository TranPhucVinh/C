#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //for open()
#include <sys/ioctl.h>

#define CHAR_DEV    "/dev/fops_character_device"

int fd;
int cmd = 10;
int argument = 123;

int main(int argc, char *argv[]) {
	fd = open(CHAR_DEV, O_RDWR);
	if (fd){
		if (ioctl(fd, cmd, &argument) == -1) {
            printf("Fail\n");
        } else {
            printf("cmd %d, argument %d\n", cmd, argument);
			printf("PID %d\n", getpid());
        }
	}
}	
