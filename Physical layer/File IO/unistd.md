``unistd.h`` provides access to the POSIX OS API.

## API

### read()

Read up to ``count`` bytes from file descriptor ``fd`` into the buffer starting at ``buf``.

```c
ssize_t read(int fd, void *buf, size_t count);
```

**File descriptor**: Represent the index of file pointer in the file table of process

3 default file descriptor values:

* 0: stdin file descriptor
* 1: stdout file descriptor
* 2: stderr file descriptor

### write()

Writes up to ``count`` bytes from the buffer starting at ``buf`` to the file referred to by the file descriptor ``fd``.

```c
ssize_t write(int fd, const void *buf, size_t count);
```

Write a string to screen

```c
#define STDOUT_FD 1
char displayedString[] = "Hello, World !";
write(STDOUT_FD, displayedString, sizeof(displayedString));
write(STDOUT_FD, "Display string", 14);
```

### close()

Close a file descriptor, so that it no longer refers to any file and may be reused. 

```c
int close(int fd);
```

## Examples

All the examples below run on both Windows and Linux.

### Example 1

Read entered value from terminal and print out

```c
#include <stdio.h>
#include <unistd.h>

#define STDIN_FD 0

int main(){
    char buffer[10];

    read(STDIN_FD, buffer, 10);
    puts(buffer);
}
```

Inside the ``while()`` loop, using ``read()`` with other ``stdout`` functions like ``puts()``, ``printf()``, ... results in garbage value printing and other ``stdout`` error.

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define STDIN_FD 	0
#define STDOUT_FD 	1

int main() {
	while(1){
		char buffer[10];
        bzero(buffer, sizeof(buffer));//Empty the previously entered buffer
		read(STDIN_FD, buffer, sizeof(buffer));
		write(STDOUT_FD, buffer, sizeof(buffer));
	}
}
```

### Example 2

Open a file to read

```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()

int fd;

int main(){
    char buffer[10];

    /*
        unistd has no API to open a file so use open() from fcntl
    */
    fd = open("test.md", O_RDONLY);
    
    read(fd, buffer, 10);
    puts(buffer);
}
```

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