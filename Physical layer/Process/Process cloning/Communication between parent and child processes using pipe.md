# R/W between parent and child process

Parent process writes int value to ``fd[1]`` and child process reads from ``fd[0]``.
<details>
	
```c
#include <stdio.h>
#include <unistd.h>

int main()  {
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
</details>
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

# R/W between parent and child process with while loop

Parent process send a string to pipe ``fd[1]`` inside a loop every 1 second, child process then reads that string out from ``fd[0]``.

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("An error occured when opening the pipe\n");
		return 1;
	}
	int pid = fork();
	if (!pid) {
        char snd_str[30];//send string
        int index = 0;
        while (1){
            sprintf(snd_str, "Hello, World !; index %d", index);
            write(fd[1], snd_str, sizeof(snd_str));
            index += 1;
            sleep(1);
        }
        close(fd[1]);
    }	
    else {
        char rcv_str[50];
        while(1){
            read(fd[0], rcv_str, sizeof(rcv_str));
            printf("Data from fd[0]: %s\n", rcv_str);
            memset(rcv_str, 0, sizeof(rcv_str));
        }
    }	
    close(fd[0]);
}
```

# R/W between parent and child process: Modified string

Parent process send a string to child process, child process receives that string and modifies it then sends back to the parent process.
<details>
	
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
</details>

# Both parent and child process read and write to pipe
Parent process write int value to pipe (fd[1]), then wait for child process to send a string to pipe (fd[0]) to read out. Child process reads out the int sent from parent then sends a string to parent.
<details>

```c
#include <stdio.h>
#include <unistd.h>

int main() {
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
		
        sleep(1);// There must be sleep() to give time for child process to read out data

        char buffer[50];
        read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(fd[0]);
	}	
	else {
		int y;
		read(fd[0], &y, sizeof(int));
		
		printf("Data from fd[0] %d\n", y);

        sleep(1);// Should have sleep() for child process to end at the same time with parent
        char child_str[] = "Child process write to parent";
        write(fd[1], child_str, sizeof(child_str));
        close(fd[1]);
	}	
}
```
</details>
