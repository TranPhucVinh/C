# fork()

```c
pid_t fork(void);
```

Clone the calling process, creating an exact copy known as the child porcess. The child process and the parent process run in separate memory spaces.

Return

* ``-1`` for errors
* ``pid`` of the child process 
* ``0`` as the child process has been created successfully

## fork execution

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

#define DELAY_TIME 1

int number;
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
		while (1){
			printf("number: %d\n", number);
			number += 1;
			sleep(DELAY_TIME);
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
            sleep(DELAY_TIME);
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

## Running multiple fork()

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

# wait()

```c
#include <sys/wait.h>
pid_t wait(int *wstatus);
```

A call to ``wait()`` blocks the calling process until one of its child processes exits or a signal is received. If ``wstatus`` is not `` NULL``, ``wait()`` store status  information in the ``wstatus``. ``wait()`` return the ``pid`` of parent process.

Take this ``fork()`` example. We want child process to print out from ``0`` to ``5`` and parent process to print out from ``6`` to ``10``.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int pid = fork();
	int number;
	if (!pid) number = 0;
	else {
		number = 6;
	}	
	for (int i = number; i < number + 5; i++) {
		printf("%d ", i);
	}	
}
```
**Result**: ``6 7 8 9 10 0 1 2 3 4``

Problem solve: Using ``wait()``

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])  {
	int pid = fork();
	int number;
	if (!pid) number = 0;
	else {
		number = 6;
		wait(NULL);
	}	
	for (int i = number; i < number + 5; i++) {
		printf("%d ", i);
	}	
}
```

**Result**: ``0 1 2 3 4 6 7 8 9 10``

``wait()`` operations:

```
    parent
   ---------🠊 wait()----🠊 resume
  |                         🠉
  |                         |
fork()                      |
  |                         |
  |--------🠊 exec() ----🠊 exit()
    child
```

So putting ``wait()`` inside child process execution gives no effect.

# Application

* [IPC with TCP socket](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/TCP#examples): 1 server communicates with multiple clients. Process cloning with ``fork()`` is used to create a new process for a file descriptor for each tcp_client every time a new connection is established.

For other example, check [Examples](Examples.md) file
