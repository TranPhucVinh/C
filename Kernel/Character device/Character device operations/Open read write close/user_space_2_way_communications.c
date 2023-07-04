#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define DEV_NAME "/dev/fops_character_device"

char buffer[20];
char write_string[] = "String written to character device";

int fd;

int main(){
    fd = open(DEV_NAME, O_RDWR);
    if(fd < 0) {
        printf("Fail to open %s\n",DEV_NAME);
        return 1;
    }
    else {
        while(1){
            write(fd, write_string, sizeof(write_string));
            
            // lseek() with offest=0 must be used to support calling read()
            // multiple times to get the proper read/non-empty read buffer
            int offset = lseek(fd, 0, SEEK_SET);
            if (!offset){
                read(fd, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                memset(buffer, 0, sizeof(buffer));
            }
            sleep(1);
        }
        close(fd);
        return 0;
    }
}
