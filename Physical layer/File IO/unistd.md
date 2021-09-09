``unistd.h`` provides access to the POSIX OS API.

## API

### read()

Read up to ``count`` bytes from file descriptor ``fd`` into the buffer starting at ``buf``.

```c
ssize_t read(int fd, void *buf, size_t count);
```

**File descriptor**: Represent the index of file pointer in the file table of process

3 default file descriptor values:

```c
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```

### write()

Writes up to ``count`` bytes from the buffer starting at ``buf`` to the file referred to by the file descriptor ``fd``.

```c
ssize_t write(int fd, const void *buf, size_t count);
```

Write a string to screen

```c
char displayedString[] = "Hello, World !";
write(STDOUT_FILENO, displayedString, sizeof(displayedString));
write(STDOUT_FILENO, "Display string", 14);
```

### close()

Close a file descriptor, so that it no longer refers to any file and may be reused. 

```c
int close(int fd);
```

### lseek

```c
off_t lseek(int fildes, off_t offset, int whence);
```

Reposition read/write file ``offset``

| whence | Description|
| ------- |:------:|
|SEEK_SET | The offset is set to offset bytes|
|SEEK_CUR|The offset is set to its current location plus offset bytes|
|SEEK_END|The offset is set to the size of the file plus offset bytes|

### pread() and pwrite()

``pread()``: Returns number of bytes read, 0 on EOF, or –1 on error

```c
ssize_t pread(int fd , void * buf , size_t count , off_t offset );
```
``pwrite()``: Returns number of bytes written, or –1 on error

```c
ssize_t pwrite(int fd , const void * buf , size_t count , off_t offset );
```

As ``pread()`` and ``pwrite()`` work with ``lseek()``, they doesn't operate with ``/dev/tty``.

## Examples

### Example 1

Open a file to read

```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()

int fd;

int main(){
    char buffer[10];

    fd = open("test.md", O_RDONLY);
    
    read(fd, buffer, 10);
    puts(buffer);
}
```

To read a file send by ``<`` operator:

```c
int main(){
    char buffer[10];
    
    read(STDIN_FILENO, buffer, sizeof(buffer));
	write(STDOUT_FILENO, buffer, sizeof(buffer));
}
```
**Run**: ``./a.out < test.c``

To a file from specific index:

```c
int fd;
char buffer[10];

fd = open("README.md", O_RDONLY);
lseek(fd, 10, SEEK_SET);
read(fd, buffer, 10);
```

``lseek()`` is not available for stdin with ``/dev/tty``

``lseek(STDIN_FILENO, 10, SEEK_SET)`` will return ``-1`` for ``/dev/tty`` but will return a normal ``fd`` for  ``./a.out < test.c``.

### Example 2

Inside the ``while()`` loop, read entered value from terminal and print out:

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	while(1){
		char buffer[10];
        bzero(buffer, sizeof(buffer));//Empty the previously entered buffer
		read(STDIN_FILENO, buffer, sizeof(buffer));
		write(STDOUT_FILENO, buffer, sizeof(buffer));
	}
}
```

**Note**: Using ``read()`` with other ``stdout`` functions like ``puts()``, ``printf()``, ... results in garbage value printing and other ``stdout`` error.

### Example 3

Open a file to write

```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()
#include <string.h> //for strlen()

int fd;

int main(){
    char buffer[] = "Hello, World !";

    fd = open("test.md", O_WRONLY);
    
    write(fd, buffer, strlen(buffer));
}
```