### fork execution

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	printf("Before forking");
	int pid = fork();
	printf("PID: %d\n", pid);
}
```
```
Before forkingPID: 1233
Before forkingPID: 0
```
``Before forking`` is printed 2 times as it is not followed by a newline.

Executing functions before ``fork()`` and get the ID of the origin and child process:

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	printf("Before forking\n");
	int pid = fork();
	if (!pid) printf("Child process has ID: %d\n", getpid());
	else printf("Parent process's ID: %d and child process's ID: %d\n", getpid(), pid);
}
```
```
Before forking
Origin process's ID: 20845 and child process's ID: 20846
Child process has ID: 20846
```
Running child process inside infinite loop:

```c
#include <stdio.h>
#include <unistd.h>

#define DELAY_TIME 1000000
int number;
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            printf("number: %d\n", number);
            number += 1;
            usleep(DELAY_TIME);
        }
    } 
	else printf("Parent process has finished execution\n");
}
```

Result:

```
username$hostname:~/pwd$ ./a.out
Parent process has finished execution
number: 0
username$hostname:~/pwd$ number: 1
number: 2
... (keeping running forever)
username$hostname:~/pwd$ ^C //Ctr+C to cancel
username$hostname:~/pwd$ ^C number: 500
number: 501
... (program will then keep running forever)
```

Running both child and parent process inside infinite loops:

```c
int child_number, parent_number;
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            printf("child process number: %d\n", child_number);
            child_number += 1;
            usleep(DELAY_TIME);
        }
    } 
	else  {
        while (1){
            printf("parent process number: %d\n", parent_number);
            parent_number += 1;
            usleep(DELAY_TIME);
        }
    }
}
```

```
username$hostname:~/pwd$ ./a.out
parent process number: 0
child process number: 0
parent process number: 1
child process number: 1
parent process number: 2
child process number: 2
username$hostname:~/pwd$ ^C //Ctr+C to cancel
```

``Ctr+C`` to cancel the program running both child and parent process inside infinite loop will end the program properly.

### Running multiple fork()

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	fork();
    fork();
    function_operation();
}
```

Then ``function_operation()`` will be run 4 times. Calling ``fork()`` ``n`` times will result in running ``function_operation()`` ``2^n`` times.

### Kill both child and parent process with SIGKILL signal

SIGKILL signal inside parent process 

```c
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            printf("child process number: %d\n", child_number);
            child_number += 1;
            usleep(DELAY_TIME);
        }
    } 
	else  {
        usleep(DELAY_TIME*5);
        kill(pid, SIGKILL);
    }
}
```

SIGKILL signal inside child process 

```c
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            usleep(DELAY_TIME*5);
            kill(pid, SIGKILL);
        }
    } 
	else  {
        while (1){
            printf("parent process number: %d\n", parent_number);
            parent_number += 1;
            usleep(DELAY_TIME);
        }
    }
}
```