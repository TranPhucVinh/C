
## Example 1

Create a FIFO

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

	int fd = open(FIFO_NAME, O_WRONLY);
	if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
	close(fd);
}
```

**Result**: File ``FIFO`` is created. The program then blocks after running ``open(FIFO_NAME, O_WRONLY)``.

That happens as opening a FIFO created by ``mkfifo()`` for reading normally blocks until some other process opens the same FIFO for writing, and vice versa.

While the program is blocking, running another program that interact with ``FIFO`` like ``cat FIFO``. It will then stop blocking.

Once you have created a FIFO special file in this way, any process can open it for reading or writing, in the same way as an ordinary file. However, it has to be open at both ends simultaneously before you can proceed to do any input or output operations on it.

For FIFO name with space like ``FIFO 1``, use ``\``, e.g ``cat FIFO\ 1``.

For better understanding of the blocking process, take this example:

```c
//Other operations like Example 1
int fd = open(FIFO_NAME, O_WRONLY);//Open for write
if (fd == -1) {
	printf("Unable to open %s", FIFO_NAME);
	return 0;
}	

while(1){
	//In while() loop, do nothing related to FIFO. Simply print out a string
	printf("Hello, World !\n");
	sleep(1);  
}
```

**Result**: This program will print out notthing when entering the while loop. To make the string ``Hello, World !`` printed out, interact with the FIFO, e.g ``cat FIFO``.

**Write int number to FIFO**

```c
int a = 98;
//Other operations like above
if (write(fd, &a, sizeof(int)) == -1) printf("Unable to write to FIFO");
```

``cat FIFO\ 1`` will then read out character ``b`` (ASCII value ``98``).

## Example 2

Communication between 2 process using FIFO. Process ``fifo_write`` writes data to FIFO ``FIFO 1`` every 1 second. Process ``fifo_read`` reads data from FIFO ``FIFO 1`` every 1 second.

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
### Example 3

Minimize float number to send as array member with 1 byte in the FIFO between 2 process with scaling factor ``65535`` [minimize_float_number_fifo_write.c](minimize_float_number_fifo_write.c) and [minimize_float_number_fifo_read.c](minimize_float_number_fifo_read.c).

**Result**

``./fifo_write``

```
Tranmit value: 15.82

Tranmit value: 59.96

Tranmit value: 21.47

Tranmit value: 19.95

Tranmit value: 8.75
```

``./fifo_read``

```
Received: 15.80

Received: 59.87

Received: 21.44

Received: 19.92

Received: 8.73
```
The received value in FIFO read different a little from FIFO write.
