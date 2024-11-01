#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#define CHAR_DEV    "/dev/fops_character_device"

int fd;
int cmd = 10;
int argument = 123;

int main(int argc, char *argv[]) {
	fd = open(CHAR_DEV, O_RDWR);
	if (fd > 0){
		if (ioctl(fd, cmd, &argument) == -1) {
           goto error_handler;
        } else {
            printf("cmd %d, argument %d, argument's address %ld\n", cmd, argument, &argument);
			printf("PID %d\n", getpid());
			//Add return here so that error_handler won't be called after finishing
			return 0;
        }
	} else goto error_handler;
	
    error_handler:
        perror("DEBUG");
        printf("Error number: %d\n", errno);
}	
