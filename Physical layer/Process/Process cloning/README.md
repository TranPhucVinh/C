# [fork()](fork().md)
```c
pid_t fork(void);
```

Clone the calling process, creating an exact copy known as the child porcess. The child process and the parent process run in separate memory spaces.

**Return**

* ``-1`` for errors
* ``pid`` of the child process is returned to the parent process.
* ``0`` as the child process has been created successfully. ``0`` is returned to the child process.
Implementation of [fork()](fork().md) includes:
* [fork() execution](fork().md#)
* [Running child process inside infinite loop](fork().md#)
* [Running multiple fork()](fork().md#)
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
# Oprhan process
A process whose parent process no more exists i.e. either finished or terminated without waiting for its child process to terminate is called an **orphan process**.
```c
#include <stdio.h>
#include <unistd.h>

#define DELAY	1

int main()
{
	int pid = fork();

	if (pid > 0) printf("parent process\n");
	else if (pid == 0)
	{
		sleep(DELAY*5);
		printf("Child process\n");
	}
	return 0;
}
```
```
username$hostname:$ ./a.out
parent process
username$hostname:$ ps
  PID TTY          TIME CMD
 3584 pts/6    00:00:00 bash
 4085 pts/6    00:00:00 a.out
 4086 pts/6    00:00:00 ps
username$hostname:$ # Wait for 5 seconds as child process, which is orphan now, is still running while parent process is killed
username$hostname:$ Child process # Child process has finished running after 5 seconds
```
# Application

* [IPC with TCP socket](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/TCP#examples): 1 server communicates with multiple clients. Process cloning with ``fork()`` is used to create a new process for a file descriptor for each tcp_client every time a new connection is established.
* [Communication between parent and child processes using pipe](Communication%20between%20parent%20and%20child%20processes%20using%20pipe.md)
* [Signal for fork()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Signal%20for%20fork().md)
* [Variable inside forked process](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Variable%20inside%20forked%20process.md)
