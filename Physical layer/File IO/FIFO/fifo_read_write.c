#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME 		 "FIFO"
#define FILE_PERMISSION	 0777 //Octal value for file permission 777
#define BUFF_SIZE        30

int fd;
char stdin_buf[BUFF_SIZE], fifo_buf[BUFF_SIZE];

int main() {
    if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("WARNING: A FIFO with the same name has already existed\n");

        if (!remove(FIFO_NAME)) {
            printf("FIFO %s has been deleted\n", FIFO_NAME);
            if (!mkfifo(FIFO_NAME, FILE_PERMISSION)) printf("FIFO %s has been recreated\n", FIFO_NAME);
        } else {
            printf("Unable to remove FIFO %s\n", FIFO_NAME);
            return 1;
        }
	} else printf("FIFO %s has been created\n", FIFO_NAME);

    while (1)
    {
        int fd = open(FIFO_NAME, O_RDWR);
        printf("Enter string to write to FIFO:");
        fgets(stdin_buf, BUFF_SIZE, stdin);
        printf("String written from stdin: %s", stdin_buf);
        write(fd, stdin_buf, BUFF_SIZE);
        read(fd, fifo_buf, BUFF_SIZE);
        printf("String read from FIFO: %s", fifo_buf);
        close(fd);
    }
    return 0;
}
