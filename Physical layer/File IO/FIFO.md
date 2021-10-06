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