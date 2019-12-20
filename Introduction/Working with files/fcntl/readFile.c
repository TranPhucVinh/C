#include <stdio.h>
#include <fcntl.h>

const char filePath[] = "test.md";
char bufferRead[20]; //store maximum 20 bytes

int fileDescription;

int main(){
    fileDescription = open(filePath, O_RDONLY); //READ ONLY
    if(fileDescription < 0)
        return 1;
    else {
        read(fileDescription, bufferRead, 10); //request 10 byte from opened file/stream
        printf("%s", bufferRead);
    }
    return 0;
}