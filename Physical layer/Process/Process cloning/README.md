# API

## fork()

```c
pid_t fork(void);
```

Clone the calling process, creating an exact copy known as the child porcess. The child process and the parent process run in separate memory spaces.

Return

* ``-1`` for errors
* ``pid`` of the child process 
* ``0`` as the child process has been created successfully

## wait()

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
