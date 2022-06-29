#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> //for open()
#include <unistd.h>
#include <sys/ioctl.h>

#define CHAR_DEV     "/dev/fops_character_device"
#define IO           _IO('a', 0)
#define IOR          _IOR('a', 0, char*)
#define IOW          _IOW('a', 0, char*)
#define IOWR         _IOWR('a', 0, char*)

char io[] = "_IO()";
char ior[] = "_IOR()";
char iow[] = "_IOW()";
char iowr[] = "_IOWR()";

struct struct_arg {
    int number;
    char string_value[30];
} struct_arg_object;

int main(int argc, char *argv[]) {
	int fd = open(CHAR_DEV, O_RDWR);
	if (fd){
		if (ioctl(fd, IO, io) == -1) {
            printf("_IO() fail\n");
        } else {
            printf("Perform _IO() successfully\n");
        }

        if (ioctl(fd, IOR, ior) == -1) {
            printf("_IOR() fail\n");
        } else {
            printf("Perform _IOR() successfully\n");
        }
        
        if (ioctl(fd, IOW, iow) == -1) {
            printf("_IOW() fail\n");
        } else {
            printf("Perform _IOW() successfully\n");
        }

        if (ioctl(fd, IOWR, iowr) == -1) {
            printf("_IOWR() fail\n");
        } else {
            printf("Perform _IOWR() successfully\n");
        }

        struct_arg_object.number = 123;
        strcpy(struct_arg_object.string_value, "Hello, World !");

        /*
            Change number arg in _IOW() to different number so
            that it is different from _IOW('a', 0, char*)
        */
        int iostruct = _IOW('a', 1, struct struct_arg_object*);

        if (ioctl(fd, iostruct, &struct_arg_object) == -1) {
            printf("_IOW() with struct struct_arg_object fail\n");
        } else {
            printf("Perform _IOW() with struct successfully\n");
        }
	}

    close(fd);
}	