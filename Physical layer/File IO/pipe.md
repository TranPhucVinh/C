# API

```c
int pipe(int fd[2]);
```

``pipe()`` create a unnamed pipe, a one-way communication channel. If successful, 2 file descriptors are stored in ``fd``. ``fd[1]`` is used for writting, ``fd[0]`` is used for reading.

``pipe()`` is a system call that can only be used for [communication inside a process](#communicate-inside-1-process) or [between the parent and child process](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Communication%20between%20parent%20and%20child%20processes%20using%20pipe.md). ``pipe()`` can't be used for communication between 2 seperated process like ``a1.out`` and ``a2.out``.

**Return**

* ``0``: success
* ``-1``: error

If a process tries to read before something is written to the pipe, the process is suspended until something is written. It means no matter which process is operating, but if ``fd[0]`` is empty, the process that perform the writing operation will be executed first. If ``fd[0]`` already has data, reading ``fd[0]`` can be executed before writing to ``fd[1]`` normally.

# Communicate inside 1 process

## Write an int variable to fd[1] and read from fd[0]

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("Fail to create a pipe\n");
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
## Write string to fd[1] and read from fd[0]

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("Fail to create a pipe\n");
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
## Write array to fd[1] and read from fd[0]
From the [write string implementation](#write-string-to-fd1-and-read-from-fd0), we can see that ``fd[1]`` and ``fd[0]`` have no fixed of storage, i.e they can reallocated their storage size to store the value written to them, which is a little similar to [vector in CPP](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/Vector.md).

Apply the same implemetation with [write string](#write-string-to-fd1-and-read-from-fd0) to any array like an int array, we have:
```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
    int wr_arr[10], rd_arr[10];
    if(pipe(fd) == -1){
		printf("Fail to create a pipe\n");
		return 1;
	}
    for (int i = 0; i < 10; i++){
        wr_arr[i] = i;
        write(fd[1], &wr_arr[i], sizeof(int));
    }
    close(fd[1]);
    
    read(fd[0], rd_arr, sizeof(int)*10);
    close(fd[0]);
    for (int i = 0; i < 10; i++){
        printf("rd_arr[%d]: %d\n", i, rd_arr[i]);
    }
}
```
Same for writing a single variable:

```c
int x = 123;
write(fd[1], &x, sizeof(int));
x = 456;
write(fd[1], &x, sizeof(int));
x = 789;
write(fd[1], &x, sizeof(int));
close(fd[1]);

int y[3];
read(fd[0], y, sizeof(int)*3);
close(fd[0]);
for (int i = 0; i < 3; i++){
	printf("y[%d]: %d\n", i, y[i]);
}
```
**Result**
```
y[0]: 123
y[1]: 456
y[2]: 789
```
# Communicate between parent and child process

[Check fork example with pipe](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Communication%20between%20parent%20and%20child%20processes%20using%20pipe.md)
