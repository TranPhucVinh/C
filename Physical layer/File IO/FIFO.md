## Example 1

Create a FIFO

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO 1"
#define FILE_PERMISSION	 0777 //Octal value for file permission 777

int main(int argc, char *argv[])  {
	char writeString[] = "Hello, World !";
	if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("Could not create FIFO file\n");
		return 1;
	}

	int fd = open(FIFO_NAME, O_WRONLY);
	printf("Opened\n");
	if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
	close(fd);
}
```

**Result**: File ``FIFO 1``, program blocks after running ``open(FIFO_NAME, O_WRONLY)``.

That happens as apening a FIFO created by ``mkfifo()`` for reading normally blocks until some other process opens the same FIFO for writing, and vice versa.

While the program is blocking, run another program that interact with ``FIFO 1`` like ``cat FIFO\ 1``. It will then stop blocking.

## Example 2

Communication between 2 process using FIFO. Process ``fifo_write`` writes data to FIFO ``FIFO 1`` every 1 second. Process ``fifo_read`` reads data from FIFO ``FIFO 1`` every 1 second.

``fifo_write.c``

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>

void delaySeconds(long seconds);

#define FIFO_NAME 		"FIFO 1"
#define FILE_PERMISSION	 0777

int main(int argc, char *argv[])  {
	char writeString[50];

	if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("Could not create FIFO file\n");
		return 1;
	}

	int fd = open(FIFO_NAME, O_WRONLY);//Open for write
	if (fd == -1) {
		printf("Unable to open %s", FIFO_NAME);
		return 0;
	}	
	printf("Opened\n");

    int index = 0;
	// for(index = 0; index < 10; index++){
	while(1){
        sprintf(writeString, "Hello, World !; index: %d\n", index);
        if (write(fd, writeString, sizeof(writeString)) != -1) {
            printf("Write message with index %d\n", index);
        }
		index += 1; 
        delaySeconds(1);    
    }

	close(fd);
}

void delaySeconds(long seconds){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long totalSecond = 0;
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}
```

``fifo_read.c``
```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>

void delaySeconds(long seconds);

#define FIFO_NAME 		"FIFO 1"
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
        delaySeconds(1);    
    }

	close(fd);
}

void delaySeconds(long seconds){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long totalSecond = 0;
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}
```
Normal file can be used for transmission between 2 process like above. ``fifo_read.c`` implements like above, ``fifo_write.c`` need some edit:

```c
#define FILE_NAME 		"temp"
#define FILE_PERMISSION	 0777

int main(int argc, char *argv[])  {
	//implementations like fifo_write.c above
	creat(FIFO_NAME, FILE_PERMISSION);
	int fd = open(FILE_NAME, O_WRONLY);//Open for write
	if (fd == -1) {
		printf("Unable to open %s", FILE_NAME);
		return 0;
	}	
	//implementations like fifo_write.c above
```

``./fifo_write``

```
Opened
Write message with index 0
Write message with index 1
Ctr+C //We stop after index 1
```

``./fifo_read``` will read:

```
Write message with index 0
Write message with index 1
Write message with index 1
Write message with index 1
Write message with index 1
//Write message with index 1 wil be read indefinitely
```
