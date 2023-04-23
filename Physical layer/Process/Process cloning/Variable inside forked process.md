# Address of a variable inside both parent and child process are the same

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

# Without shared memory, changing variable value in parent/child process won't effect the left one

Although global variable ``a`` has the same address value in both parent and child process, changing its value in the parent process won't affect the child process.
Changing variable value in the child process won't effect the parent:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    int a = 12;
    pid_t pid = fork();

    if( pid == 0 ) {
		a = 34;
        printf("Child process, *a = %d\n", a);//Child process, *a = 34
    }
    else {
		wait(NULL);
        printf("Parent process, *a = %d\n", a);//Parent process, *a = 12
    }
    return 0;
}
```
Using pointer

```c
int main(void){
    int *a;
	a = (int*) malloc(sizeof(int) * 1);
	*a = 12;
    pid_t pid = fork();

    if( pid == 0 ) {
		*a = 34;
        printf("Child process, *a = %d\n", *a);//Child process, *a = 34
    }
    else {
		wait(NULL);
        printf("Parent process, *a = %d\n", *a);//Parent process, *a = 12
    }
    return 0;
}
```
Changing variable value inside the parent process won't effect the child process:
```c
int main(void){
    int *a;
	a = (int*) malloc(sizeof(int) * 1);
	*a = 12;
    pid_t pid = fork();

    if( pid == 0 ) {
        printf("Child process, *a = %d\n", *a);//Child process, *a = 12
    }
    else {
		*a = 34;
        printf("Parent process, *a = %d\n", *a);//Parent process, *a = 34
    }
    return 0;
}
```

That happens as both parent and child process have different address space. To make change of variable inside a child process to effect the parent or in reverse, use **shared memory** with [mmap()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Virtual%20memory.md#mmap).

# With shared memory, changing variable value in parent/child process will effect the left one

Changing variable value from child process which will effect parent process

```c
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define PAGE_SIZE   4048
#define NO_FD       -1  //No file descriptor used for shared memory
#define BASE_ADDR   0   //No specific base address to set in shared memory

int *a;

int main(void){
	//Must put this mmap() setup before fork()
	a = (int *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
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

```
Child process, *a = 34
Parent process, *a = 34
```
Changing variable value inside the parent process will effect the child process:
```c
int *a;

int main(void){
	//Must put this mmap() setup before fork()
	a = (int *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *a = 12;

    pid_t pid = fork();
    
    if( pid == 0 ) {
        printf("Child process, *a = %d\n", *a);//Child process, *a = 34
    }
    else {
		*a = 34;
        printf("Parent process, *a = %d\n", *a);//Parent process, *a = 12
    }
    return 0;
}
```
```
Parent process, *a = 34
Child process, *a = 34
```
