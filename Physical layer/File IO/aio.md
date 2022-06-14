``aio``: POSIX asynchronous I/O overview

### Example

Read content of a file

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <aio.h>
#include <string.h>
#include <stdlib.h>//for memset()
#include <errno.h> //for EINPROGRESS

#define SIZE_TO_READ 200

char filePath[] = "test.c";

int main(){
   int fileDescriptor = open(filePath, O_RDONLY); //READ ONLY

   if(fileDescriptor == -1){
      printf("Unable to open file\n");
      return 0;
   }
   char *readBuffer;

   /* Initial memory allocation */
   readBuffer = (char *) malloc(SIZE_TO_READ);

   struct aiocb controlBlock;

   memset(&controlBlock, 0, sizeof(struct aiocb));
   controlBlock.aio_nbytes = SIZE_TO_READ;
   controlBlock.aio_fildes = fileDescriptor;
   controlBlock.aio_offset = 0;
   controlBlock.aio_buf = readBuffer;

   if (aio_read(&controlBlock) == -1){
      printf("Unable to create request");
      close(fileDescriptor);
   }

   printf("Request enqueued\n");

   //wait until the request has finished
   while(aio_error(&controlBlock) == EINPROGRESS)
   {
      printf("Reading ...\n");
   }

   int numBytes = aio_return(&controlBlock);
   if (numBytes != -1) printf("%s\n", readBuffer);
}
```

Compile: ``gcc test.c -lrt``

``aio_read(&controlBlock)`` when called will create a thread outside the running process (``a.out``) to read the file, so that the program will not be blocked when reading.

