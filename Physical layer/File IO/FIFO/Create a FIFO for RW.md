# Singly open FIFO with O_WRONLY and O_RDONLY mode

Create a FIFO then open it with ``O_WRONLY`` to **write** data to it

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

**Blocking Behavior**: When one process opens a FIFO for reading (``O_RDONLY``), it will block until another process opens the same FIFO for writing (``O_WRONLY``). Similarly, the writing process will block if there's no reader on the other end.

For FIFO name with space like ``FIFO 1``, use ``\``, e.g ``cat FIFO\ 1``.

**Write int number to FIFO**

```c
int a = 98;
//Other operations like above
if (write(fd, &a, sizeof(int)) == -1) printf("Unable to write to FIFO");
```

``cat FIFO\ 1`` will then read out character ``b`` (ASCII value ``98``).

## Simple IPC programs with a FIFO

``fifo_read.c`` will read the string sent from ``fifo_write.c``.

``fifo_read.c``

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"
#define FILE_PERMISSION	 0777 //Octal value for file permission 777
#define BUFF_SIZE   10
int main()  {
	if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("WARNING: A FIFO with the same name has already existed\n");

        //Use unlink() or remove() to remove the existed FIFO with the same name if existed
        if (!remove(FIFO_NAME)) {
            printf("FIFO %s has been deleted\n", FIFO_NAME);

            //Then create that FIFO again
            if (!mkfifo(FIFO_NAME, FILE_PERMISSION)) printf("FIFO %s has been recreated\n", FIFO_NAME);
        } else {
            printf("Unable to remove FIFO %s\n", FIFO_NAME);
            return 1;
        }
	} else printf("FIFO %s has been created\n", FIFO_NAME);

	int fd = open(FIFO_NAME, O_RDONLY);
    char buffer[BUFF_SIZE];
    bzero(buffer, sizeof(buffer));//Empty the buffer before entering value
    read(fd, buffer, sizeof(buffer));
    printf("Entered string: %s\n", buffer);
	close(fd);
}
```

``fifo_write.c``

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"

int main()  {
	char writeString[] = "Hello, World !";

	int fd = open(FIFO_NAME, O_WRONLY);
	if (write(fd, writeString, sizeof(writeString)) == -1) printf("Unable to write to FIFO");
	else printf("Write to FIFO successfully\n");
	close(fd);
}
```

**Note**: As FIFO works fundamentally like a file so it must be opened with the right mode for proper operation, i.e to read (with ``read()``), open with ``O_RDONLY``, to write, open with ``O_WRONLY``.

# Open FIFO with O_RDWR mode

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

As implementing above when opening FIFO with ``WRITE_ONLY`` mode, the FIFO will be blocked until another process open it to read (with ``O_RDONLY``) mode. So when opening with ``O_RDWR`` mode, the FIFO won't be blocked by ``open()`` and will execute until ``close(fd)``. Then another process opening that FIFO file won't be able to read the previous written data in that FIFO as **the FIFO now is not opened at both ends simultaneously**.

**Open a FIFO with O_RDWR mode to R/W**

This example is intended to demonstrate the behavior of a FIFO opened inside a process for its internal communication.

Write a string in ``stdin`` to store in ``stdin_buf`` buffer. Then write that ``stdin_buf`` buffer to a FIFO opened with O_RDWR. Finally read that string out from the FIFO into ``fifo_buf``: [fifo_read_write.c](fifo_read_write.c)
