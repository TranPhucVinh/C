## Example 1: File operations

**Open a file to read**

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

**Read the whole file by chunk**:

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define READ_CHUNK_SIZE 3//This can be any >0 value

const char file_path[] = "README.md";
char buffer_read[READ_CHUNK_SIZE];

int fd;

int main(){
	fd = open(file_path, O_RDONLY);
	if(fd < 0) return 1;
	else {
		while(read(fd, buffer_read, READ_CHUNK_SIZE)){
			printf("%s", buffer_read);

			//Clear buffer every time reading to avoid garbage value
			bzero(buffer_read, READ_CHUNK_SIZE);
		}
		printf("\n");
	}
	close(fd);
    return 0;
}
```

**Open a file to write**

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

## Example 2: Terminal and peripheral operations

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

Read entered data from the current running terminal (``/dev/tty``)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const char filePath[] = "/dev/tty";
char bufferRead[20];

int fileDescription;
void delaySeconds(long seconds);

int main(){
   fileDescription = open(filePath, O_RDONLY); //READ ONLY
   while(1){
	   bzero(bufferRead, sizeof(bufferRead));
      if(fileDescription < 0) return 1;
      else {
         read(fileDescription, bufferRead, sizeof(bufferRead));
         printf("%s", bufferRead);
      }
   }
    return 0;
}
```
Read data from USB port (``/dev/ttyUSB0``, ``/dev/ttyACM0``,...)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

const char filePath[] = "/dev/ttyACM0";
char bufferRead[20];

int fileDescription;
void delaySeconds(long seconds);

int main(){
   fileDescription = open(filePath, O_RDONLY); //READ ONLY
   while(1){
      if(fileDescription < 0) return 1;
      else {
         read(fileDescription, bufferRead, sizeof(bufferRead));
         printf("%s", bufferRead);
      }
      memset(bufferRead, 0, sizeof(bufferRead));
		delaySeconds(1);
   }
    return 0;
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