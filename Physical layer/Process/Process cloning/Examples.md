# Signal for fork()

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

# Variable inside forked process

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

That happens as both parent and child process have different address space. To make change of variable inside a child process to effect the parent or in reverse, use **shared memory** with [mmap()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Virtual%20memory.md#mmap).

Change variable value from child process which will effect parent process:

```c
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define PAGE_SIZE   4048
#define NO_FD       -1  //No file descriptor used for shared memory
#define BASE_ADDR   0   //No specific base address to set in shared memory

uint32_t *a;

int main(void){
	//Put this mmap() setup before fork()
	a = (uint32_t *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *a = 12;

    pid_t pid = fork();
    
    if( pid == 0 ) {
        *a = 34;
        printf("Child process, *a = %d\n", *a);//Child process, *a = 34
    }
    else {
		wait(NULL);//Wait for child process to finish
        printf("Parent process, *a = %d\n", *a);//Parent process, *a = 12
    }
    return 0;
}
```
