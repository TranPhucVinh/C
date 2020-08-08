#include <stdio.h>
#include <fcntl.h>

const char filePath[] = "test.md";
char bufferWrite[] = "Hello, World!";

int fileDescription;

int main(){
    fileDescription = open(filePath, O_WRONLY); //READ ONLY
    if(fileDescription < 0)
        return 1;
    else {
        write(fileDescription, bufferWrite, sizeof(bufferWrite)); //request 10 byte from opened file/stream
    }
    return 0;
}