**Example 1**: Write value to ``fd[1]`` and read from ``fd[0]`` from the origin and child process.

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
		printf("Writting to fd[1]\n");
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}	
	else {
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Data from fd[0] %d\n", y);
	}	
}
```

For string:

```c
if (!pid) {
	char displayedString[] = "Hello, World !";
	printf("Writing to fd[1]\n");
	write(fd[1], &displayedString, sizeof(displayedString));
	close(fd[1]);
}	
else {
	char receivedString[50];
	read(fd[0], receivedString, sizeof(receivedString));
	close(fd[0]);
	printf("Data from fd[0]: %s\n", receivedString);
}	
```

**Note**: User must create the ``pipe()`` before forking the process. If the pipe is created after forking, the program will be hanged.