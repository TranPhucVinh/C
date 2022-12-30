# R/W between parent and child process

Write int value to ``fd[1]`` in parent process and read from ``fd[0]`` in child process.

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

# R/W between parent and child process: Modified string

Parent process send a string to child process, child process receives that string and modifies it then sends back to the parent process.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("An error occured when opening the pipe\n");
		return 1;
	}
	int pid = fork();
	char originMessage[] = "Message";
	
	char receivedString[100];
	char sendString[100];
	if (!pid){
		if (read(fd[0], receivedString, sizeof(receivedString)) == -1) printf("Unable to read data from fd[0]");
		else {
			printf("Execute 1\n");
			sprintf(sendString, "%s: Message from forked process send back to origin message", receivedString);
		}
		if (write(fd[1], sendString, sizeof(sendString)) == -1) printf("Unable to write data to fd[1]");
		else printf("Execute 2\n");
	} else {
		if (write(fd[1], originMessage, sizeof(originMessage)) == -1) printf("Unable to write data to fd[1]");
		wait(NULL);
		if (read(fd[0], receivedString, sizeof(receivedString)) == -1) printf("Unable to read data from fd[0]");	
		else printf("Data from fd[0]: %s\n", receivedString);
	}

	close(fd[1]);
	close(fd[0]);
}
```
