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