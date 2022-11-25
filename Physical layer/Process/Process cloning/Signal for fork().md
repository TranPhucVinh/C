## Terminate both child and parent process with SIGKILL signal

``SIGKILL`` signal inside parent process: Run child process for 5 seconds then kill parent process by ``SIGKILL``  which will stop the whole program includes both parent and child process.

```c
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            printf("child process number: %d\n", child_number);
            child_number += 1;
            sleep(DELAY_TIME);
        }
    } 
	else  {
        sleep(DELAY_TIME*5);
        kill(pid, SIGKILL);
    }
}
```

``SIGKILL`` signal inside child process: Run child process for 5 seconds then kill it by ``SIGKILL``  which will stop the whole program includes both parent and child process.
 
```c
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            sleep(DELAY_TIME*5);
            kill(pid, SIGKILL);
        }
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

## Stop and continue process with fork() by signal

In parent process, if ``number`` is ``5``, stop for parent process for 5 seconds then continues

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>   

#define DELAY_TIME 1000000
int number;
int main(int argc, char *argv[])  {
	int pid = fork();
	if (pid) {
        while (1){
            printf("number: %d\n", number);
            if (number == 5){
                kill(pid, SIGSTOP);
                usleep(DELAY_TIME*5);
                kill(pid, SIGCONT);
            } 
            number += 1;
            usleep(DELAY_TIME);
        }
    }
}
```
If using that flow inside the child process, the program will be blocked when ``number`` reaches ``5``:

```c
int pid = fork();
if (!pid) {
        while (1){
            printf("number: %d\n", number);
            if (number == 5){
                kill(pid, SIGSTOP);
                usleep(DELAY_TIME*5);
                kill(pid, SIGCONT);
            } 
            number += 1;
            usleep(DELAY_TIME);
        }
    }
```
