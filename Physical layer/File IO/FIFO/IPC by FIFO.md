# Create a FIFO for R/W

Create a FIFO and **write** data to it

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"
#define FILE_PERMISSION	 0777 //Octal value for file permission 777

int main(int argc, char *argv[])  {
	char writeString[] = "Hello, World !";

	if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("WARNING: A FIFO with the same name has already existed\n");

        //Use unlink() or remove() to remove the existed FIFO with the same name if existed
        if (!remove(FIFO_NAME)) {
            printf("FIFO %s has been deleted\n", FIFO_NAME);

            //Then create that FIFO again
            if (!mkfifo(FIFO_NAME, FILE_PERMISSION)) printf("FIFO %s has been recreated\n", FIFO_NAME);
        } else {
            printf("Unable to remove FIFO %s", FIFO_NAME);
            return 1;
        }
	} else printf("FIFO %s has been created\n", FIFO_NAME);

	int fd = open(FIFO_NAME, O_WRONLY);//The program will blocks right after running open(FIFO_NAME, O_WRONLY)
	if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
	else printf("Write to FIFO successfully\n");
	close(fd);
}
```

**Result**: File ``FIFO`` is created. The program then blocks right after running ``open(FIFO_NAME, O_WRONLY)``.

That happens as opening a FIFO created by ``mkfifo()`` for writing normally blocks until some other process opens the same FIFO for reading, and vice versa.

In this case, while the program is blocking, running another program to **read** the ``FIFO`` like ``cat FIFO`` will read out the data written into that FIFO then the FIFO will then stop blocking.

``cat FIFO`` will result in ``Hello, World !`` (the string written before to that FIFO).

**Once you have created a FIFO special file in this way, any process can open it for reading or writing, in the same way as an ordinary file. However, it has to be open at both ends simultaneously before you can proceed to do any input or output operations on it.**

For FIFO name with space like ``FIFO 1``, use ``\``, e.g ``cat FIFO\ 1``.

**Write int number to FIFO**

```c
int a = 98;
//Other operations like above
if (write(fd, &a, sizeof(int)) == -1) printf("Unable to write to FIFO");
```

``cat FIFO\ 1`` will then read out character ``b`` (ASCII value ``98``).

**Change opening mode**: In the source code above, if we change the opening mode to READ and WRITE, the whole program will not block after the FIFO created successfully

```c
int fd = open(FIFO_NAME, O_RDWR);
if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
else printf("Write to FIFO successfully\n");
close(fd);
```

**Result**

```sh
username@hostname:$ ./a.out
WARNING: A FIFO with the same name has already existed
FIFO FIFO has been deleted
FIFO FIFO has been recreated
Write to FIFO successfully
```

As implementing above when opening FIFO with ``WRITE_ONLY`` mode, the FIFO will be blocked until another process open it to read (with ``O_RDONLY``) mode. So when opening with ``O_RDWR`` mode, the FIFO won't be blocked and will be closed right after ``Write to FIFO successfully``. Then another process opening that FIFO file won't be able to read the previous written data in that FIFO as **the FIFO now is not opened at both ends simultaneously**.

# IPC by FIFO

Process ``fifo_write`` writes data to FIFO ``FIFO 1`` every 1 second. Process ``fifo_read`` reads data from FIFO ``FIFO 1`` every 1 second.

``fifo_write.c``

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

``fifo_read.c``
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
**Note**: When sending/receiving int array with FIFO, the sending/receiving size in ``read()`` and ``write()`` must be:

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
