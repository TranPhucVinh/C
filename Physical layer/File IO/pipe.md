## API

```c
int pipe(int fd[2]);
```

``pipe()`` create a one-way communication channel (pipe). If successful, 2 file descriptors are stored in ``fd``. ``fd[1]`` is used for writting, ``fd[0]`` is used for reading.

``pipe()`` is a system call that can only be used for communication inside a process or between the parent and child process. ``pipe()`` can't be used for communication between 2 seperated process like ``a1.out`` and ``a2.out``.

**Return**

* ``0``: success
* ``-1``: error

If a process tries to read before something is written to the pipe, the process is suspended until something is written. It means no matter which process is operating, but if ``fd[0]`` is empty, the process that perform the writing operation will be executed first. If ``fd[0]`` already has data, reading ``fd[0]`` can executed before writing to ``fd[1]`` normally.

## Examples

### Example 1: Communicate inside 1 process

Write value to ``fd[1]`` and read from ``fd[0]``

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("An error occured when opening the pipe\n");
		return 1;
	}
	int x = 123;
	printf("Writing x to fd[1]\n");
	write(fd[1], &x, sizeof(int));
	close(fd[1]);
	int y;
	read(fd[0], &y, sizeof(int));
	close(fd[0]);
	printf("Data from fd[0]: %d\n", y);
}
```
For string:

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("An error occured when opening the pipe\n");
		return 1;
	}
	char displayedString[] = "Hello, World !";
	printf("Writing x to fd[1]\n");
	write(fd[1], displayedString, sizeof(displayedString));
	close(fd[1]);

	char receivedString[50];
	read(fd[0], receivedString, sizeof(receivedString));
	close(fd[0]);
	printf("Data from fd[0]: %s\n", receivedString);
}
```
### Example 2: Communicate between parent and child process

[Check fork example with pipe](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/pipe%20examples.md)
