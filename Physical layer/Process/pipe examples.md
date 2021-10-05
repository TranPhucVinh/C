```c
int pipe(int fd[2]);
```

``pipe()`` create a one-way communication channel (pipe). If successful, 2 file descriptors are stored in ``fd``. ``fd[1]`` is used for writting, ``fd[0]`` is used for reading.

**Return**

* ``0``: success
* ``-1``: error

If a process tries to read before something is written to the pipe, the process is suspended until something is written. It means no matter which process is operating, the process that perform the writing operation will be executed first.

**Example 1**: Write value to ``fd[1]`` and read from ``fd[0]``
```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("An error occured when opening the pipe\n");
		return 1;
	}
	int pid = fork();
	if (!pid) {
		int x = 123;
		printf("Writting to x value\n");
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}	
	else {
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Data from forked process %d\n", y);
	}	
}
```