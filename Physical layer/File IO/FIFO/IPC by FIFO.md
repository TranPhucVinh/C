# Features

Process ``fifo_write`` writes data to FIFO ``FIFO 1`` every 1 second. Process ``fifo_read`` reads data from FIFO ``FIFO 1`` every 1 second.

# fifo_write.c

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"
#define FILE_PERMISSION	 0777

int main(int argc, char *argv[])  {
	char write_string[50];

	if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("WARNING: A FIFO with the same name has already existed\n");

        //Use unlink() to remove the existed FIFO with the same name if existed
        if (!remove(FIFO_NAME)) {
            printf("FIFO %s has been deleted\n", FIFO_NAME);

            //Then create that FIFO again
            if (!mkfifo(FIFO_NAME, FILE_PERMISSION)) printf("FIFO %s has been recreated\n", FIFO_NAME);
        } else {
            printf("Unable to remove FIFO %s", FIFO_NAME);
            return 1;
        }
	} else printf("FIFO %s has been created\n", FIFO_NAME);

	int fd = open(FIFO_NAME, O_WRONLY);//Open for write
	if (fd == -1) {
		printf("Unable to open %s", FIFO_NAME);
		return 0;
	}	
	printf("Opened\n");

    int index = 0;
	while(1){
        sprintf(write_string, "Hello, World !; index: %d\n", index);
        if (write(fd, write_string, sizeof(write_string)) != -1) {
            printf("Write message with index %d\n", index);
        }
		index += 1; 
        sleep(1);  
    }

	close(fd);
}
```

# fifo_read.c

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME 		"FIFO"
#define FILE_PERMISSION	 0777

int main(int argc, char *argv[])  {
	char readBuffer[50];
    
	int fd = open(FIFO_NAME, O_RDONLY);//Open for read
	if (fd == -1) {
		printf("Unable to open %s", FIFO_NAME);
		return 0;
	}	

	printf("Opened\n");

    while(1){
        read(fd, readBuffer, sizeof(readBuffer));
        printf("Received: %s", readBuffer);
        sleep(1); 
    }

	close(fd);
}
```

# Note

When sending/receiving int array with FIFO, the sending/receiving size in ``read()`` and ``write()`` must be:

```c
write(fd, array, sizeof(int) * ARRAY_SIZE);
```

```c
read(fd, read_buffer, sizeof(int) * ARRAY_SIZE);
``` 

We must ``sizeof(int) * ARRAY_SIZE`` because size of int is always greater than 1 byte.

E.g:

``fifo_write.c``

```c
int array[2] = {1, 2};

if (write(fd, array, sizeof(int) * 2) != -1) {
    printf("Write message with index %d\n", index);
}
```	

``fifo_read.c``

```c
while(1){
	read(fd, read_buffer, sizeof(int) * 2);
	printf("index 0: %d, index 1: %d\n", read_buffer[0], read_buffer[1]);
	sleep(1); 
}
```

If using wrong sending/receiving size, e.g ``write(fd, array, ARRAY_SIZE)``, then the received value will be garbage:

```
index 0: -324141055, index 1: 32767
```
