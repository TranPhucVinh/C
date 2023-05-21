# Signal handler is called in both parent and child process
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>   

#define DELAY_TIME   1   
char displayed_string[50];

void signal_handler(int signal_number){
	int sz = snprintf(displayed_string, sizeof(displayed_string), "%d; Signal %d is caught\n", getpid(), signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
    exit(1);
}

int main(int argc, char *argv[])  {
    memset(displayed_string, 0, sizeof(displayed_string));
    signal(SIGINT, signal_handler);
	int pid = fork();
	if (!pid) {
        while (1) sleep(DELAY_TIME);
    } 
	else {
        while (1) sleep(DELAY_TIME);
    }
}
```
**Result**
```
^C25045; Signal 2 is caught
25046; Signal 2 is caught
```
# Kill child process while parent process keeps running normally

Kill only the child process by ``getpid()`` while parent process keeps running normally:

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>   

#define DELAY_TIME 1

int child_number, parent_number;

int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
		sleep(DELAY_TIME*5);
		printf("Child process is terminated\n");
		kill(getpid(), SIGKILL);
    } 
	else  {
        while (1){
            printf("parent process number: %d\n", parent_number);
            parent_number += 1;
            sleep(DELAY_TIME);
        }
    }
}
```
# SIGCHLD
With source code like [Kill child process while parent process keeps running normally](#kill-child-process-while-parent-process-keeps-running-normally), caught **SIGCHLD** signal when child process is terminated
```c
void sigchild(int signal_number){
    char displayed_string[50];
    memset(displayed_string, 0, sizeof(displayed_string));
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal SIGCHLD %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
    exit(1);
}

int main(int argc, char *argv[])  {
	int pid = fork();
	signal(SIGCHLD, sigchild);
	if (!pid) {
		sleep(DELAY_TIME*5);
		printf("Child process is terminated\n");
		kill(getpid(), SIGKILL);
    } 
    // Other operations are like: Kill child process while parent process keeps running normally
}
```
