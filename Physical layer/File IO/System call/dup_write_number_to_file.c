#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define WRITE_SIZE 5

int number = 0;
char *write_buffer;

int main()
{
    int fd = open("test.txt", O_WRONLY | O_APPEND);
      
    if(fd < 0) printf("Error opening the file\n");
  
    int copy_fd = dup(fd);

    //Use dynamic string with strlen() to avoid garbage value writting
    write_buffer = (char*) malloc(WRITE_SIZE);

    while(number < 100){
        sprintf(write_buffer, "%d\n", number);
        write(fd, write_buffer, strlen(write_buffer));      
        number += 1;
        sprintf(write_buffer, "%d\n", number);
        write(copy_fd, write_buffer, strlen(write_buffer));
        number += 1;
    }  
    free(write_buffer);
    return 0;
}