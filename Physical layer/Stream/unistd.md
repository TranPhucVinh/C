### read()

Read up to ``count`` bytes from file descriptor ``fd`` into the buffer starting at ``buf``.

```c
ssize_t read(int fd, void *buf, size_t count);
```

**File descriptor**: Represent the index of file pointer in the file table of process

Value:

* 0: STDIN
* 1: STDOUT
* 2: STDERR

### write()

Writes up to ``count`` bytes from the buffer starting at ``buf`` to the file referred to by the file descriptor ``fd``.

```c
ssize_t write(int fd, const void *buf, size_t count);
```

Write a string to screen

```c
#define STDOUT_FD 0
char displayedString = "Hello, World !";
write(STDOUT_FD, displayedString, sizeof(displayedString));
```

Notice that you can't use ``write()`` more than 2 times because only one ``write()`` is effected.

```c
write(STDOUT_FD, displayedString, sizeof(displayedString));//This line will be printed
write(STDOUT_FD, displayedString, sizeof(displayedString));//This line will not be printed
```

### Example

All the examples below run on both Windows and Linux.

**Example 1**: Read entered value from terminal and print out

```c
#include <stdio.h>
#include <unistd.h>

int main(){
    char buffer[10];

    read(0, buffer, 10);
    puts(buffer);
}
```

**Example 2**: Open a file to read

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

For ``open()``, check ``Stream/File system/API.md``

**Example 3**: Open a file to write

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