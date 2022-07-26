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

### Terminate both child and parent process with SIGKILL signal

``SIGKILL`` signal inside parent process 

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

``SIGKILL`` signal inside child process 

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
### Stop and continue process with fork() by signal

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

## Variable inside forked process

Address of a variable inside both parent and child process are the same:

```c
int main(void){
    int *a;
    pid_t pid = fork();

    if( pid == 0 ) {
        a = (int*) malloc(sizeof(int) * 1);
        printf("%p\n", a);//0x564e0d4e22a0
    }
    else {
        a = (int*) malloc(sizeof(int) * 1);
        printf("%p\n", a);//0x564e0d4e22a0
    }
    return 0;
}
```

### Changing variable value in parent/child process won't effect the left one

Although global variable ``a`` has the same address value in both parent and child process, changing its value in the parent process won't affect the child process:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int *a;
    pid_t pid = fork();

    if( pid == 0 ) {
        a = (int*) malloc(sizeof(int) * 1);
        *a = 12;
        printf("%d\n", *a);//12
    }
    else {
        printf("%d\n", *a);//Segmentation fault
    }
    return 0;
}
```

Changing variable value in the child process won't effect the parent:

```c
int main(void){
    int a = 1;
    pid_t pid = fork();

    if( pid == 0 ) {
        a = 2;
        printf("Child process, a = %d\n", a);//Child process, a = 2
    }
    else {
        printf("Parent process, a = %d\n", a);//Parent process, a = 1; i.e: can't be changed by the child process
    }
    return 0;
}
```

The same issue will happen if changing value inside the parent process as this won't effect the child process:

```c
int a = 1;
if( pid == 0 ) {
    
    printf("Child process, a = %d\n", a);//Child process, a = 1; i.e: can't be changed by the parent process
}
else {
    a = 2;
    printf("Parent process, a = %d\n", a);//Parent process, a = 2
}
```

That happens as both parent and child process have different address space. To make change of variable inside a child process to effect the parent or in reverse, use **shared memory** with ``mmap()``

```c
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

#define PAGE_SIZE   4048
#define NO_FD       -1  //No file descriptor used for shared memory
#define BASE_ADDR   0   //No specific base address to set in shared memory

uint32_t *a;

int main(void){
    pid_t pid = fork();
    a = (uint32_t *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *a = 12;

    if( pid == 0 ) {
        *a = 34;
        printf("Child process, *a = %d\n", *a);//Child process, *a = 34
    }
    else {
        printf("Parent process, *a = %d\n", *a);//Parent process, *a = 12
    }
    return 0;
}
```
