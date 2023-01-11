# stdio and file pointer API

* [stdin and stdout API](stdin%20and%20stdout%20API.md)
* [File pointer API](File%20pointer%20API.md)


## [stdio examples](stdio%20examples.md)

* [Using formated output in printf()](stdio%20examples.md#using-formated-output-in-printf)
* [Print out an entered string and an entered character](stdio%20examples.md#print-out-an-entered-string-and-an-entered-character)
* [Compare the entered string](stdio%20examples.md#compare-the-entered-string)
* [Print out all files inside a folder with dirent.h](stdio%20examples.md#print-out-all-files-inside-a-folder-with-direnth)

## [File pointer examples](File%20pointer%20examples.md)

# Other API

## aio.h

``aio``: POSIX asynchronous I/O.

The POSIX asynchronous I/O (AIO) interface allows applications to initiate one or more I/O operations that are performed asynchronously (i.e., in the background).

**Example**: Read content of a file

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

## rename()

Rename a file

```c
int rename(const char *old_filename, const char *new_filename)
```

**Return**: ``0`` if rename successfully, ``1`` if unable to rename file

## remove()

Remove a file

```c
int remove(const char *filename);
```

## perror()

Print out message describe error in ``stderr``.

```c
void perror(const char *str)
```

**Example**

```c
int main() {
	perror("hello"); //hello: Success
}
```

**Example: No such file or directory**

```c
int main() {
	FILE *file;
	file = fopen("text.abc", "r");
	if (file == NULL) {
		perror("Error");//Error: No such file or directory
	}
}
```
