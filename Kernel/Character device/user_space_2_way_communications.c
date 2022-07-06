#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define DEV_NAME "/dev/fops_character_device"

char buffer[20];
char write_string[] = "String writes to character device";

int fd;

int main(){
    fd = open(DEV_NAME, O_RDWR); //READ ONLY
    while(1){
        if(fd < 0) {
            printf("Fail to open %s\n",DEV_NAME);
            return 1;
        }
        else {
            write(fd, write_string, sizeof(write_string));
            read(fd, buffer, sizeof(buffer));
            printf("%s", buffer);
        }
        memset(buffer, 0, sizeof(buffer));
        sleep(1);
    }
    return 0;
}