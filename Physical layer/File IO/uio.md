# API

The ``readv()`` and ``writev()`` system calls perform scatter-gather I/O.

The ``preadv()`` and ``pwritev()`` perform ``readv()`` and ``writev()`` with offset.

```c
#include <sys/uio.h>

//Returns number of bytes read, 0 on EOF, or –1 on error
ssize_t readv(int fd, const struct iovec * iov, int iovcnt);

//Returns number of bytes written, or –1 on error
ssize_t writev(int fd, const struct iovec * iov, int iovcnt);

ssize_t preadv(int fd, const struct iovec * iov, int iovcnt, off_t offset);

ssize_t pwritev(int fd, const struct iovec * iov, int iovcnt, off_t offset);
```

# Examples

## Read content from a file to stored in multiples string array

```c
#include <stdio.h>
#include <sys/uio.h>//for readv()
#include <fcntl.h>

#define TOTAL_IOVECTOR 3

const char filePath[] = "README.md";

int fileDescription;

struct iovec iov[3];
char readString1[20], readString2[20], readString3[20];

int main(){
    //Initiate parameter to for iov
    iov[0].iov_base = readString1;
    iov[0].iov_len = sizeof(readString1);
    
    iov[1].iov_base = readString2;
    iov[1].iov_len = sizeof(readString2);

    iov[2].iov_base = readString3;
    iov[2].iov_len = sizeof(readString3);

	fileDescription = open(filePath, O_RDONLY); //READ ONLY
    if (readv(fileDescription, iov, TOTAL_IOVECTOR) == -1) printf("Unable to read file\n");
    else {
        printf("readString1 %s\n", readString1);
        printf("readString2 %s\n", readString2);
        printf("readString3 %s\n", readString3);
    }    
    return 0;
}
```

``readString1[20]``, ``readString2[20]`` and ``readString3[20]`` then will read from 3 contiguous location from file ``README.md``, i.e ``readString2[20]`` will then read from the file location where ``readString1[20]`` stops.

Get entered string from terminal and store to 3 string array

```c
const char filePath[] = "/dev/tty";

int main(){
    /*
        Initiate parameter to for iov
    */

    while (1){
        fileDescription = open(filePath, O_RDONLY); //READ ONLY
        if (readv(fileDescription, iov, TOTAL_IOVECTOR) == -1) printf("Unable to read file\n");
        else {
            printf("readString1 %s\n", readString1);
            printf("readString2 %s\n", readString2);
            printf("readString3 %s\n", readString3);
        }    
    }
    return 0;
}
```

## Write multiples string stored in ``struct iovec`` to a file

```c
#include <stdio.h>
#include <sys/uio.h>//for writev()
#include <fcntl.h>

#define TOTAL_IOVECTOR 3

const char filePath[] = "temp.txt";

int fileDescription;

struct iovec iov[3];
char writeString1[] = "Write string 1";
char writeString2[] = "Write string 2";
char writeString3[] = "Write string 3";

int main(){
    //Initiate parameter to for iov
    iov[0].iov_base = writeString1;
    iov[0].iov_len = sizeof(writeString1);
    
    iov[1].iov_base = writeString2;
    iov[1].iov_len = sizeof(writeString2);

    iov[2].iov_base = writeString3;
    iov[2].iov_len = sizeof(writeString3);

    fileDescription = open(filePath, O_WRONLY);//Write only
    if (writev(fileDescription, iov, TOTAL_IOVECTOR) == -1) printf("Unable to write to file\n");
    return 0;
}
```

Write out to ``stdout``:

```c
writev(STDOUT_FILENO, iov, TOTAL_IOVECTOR)
```