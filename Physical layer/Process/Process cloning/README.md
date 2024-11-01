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
# [waitpid()](waitpid().md)
``waitpid()`` system call suspends execution of the calling process until a child specified by pid argument has changed state. It is used in parent process to monitor the state change of its child process.
# vfork()
```c
pid_t vfork(void);
```
``vfork()`` creates a child process and block parent. 

Check [Running both child and parent process inside infinite loops when creating the child process]() with both fork() and vfork() for comparison.

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
## Orphan process can't receive signals registered from its parent process
An orphan process can't receive any signal previously registered from its parent process as its parent has died.
In this example, we register SIGINT for later Ctr+C with the intention to stop parent and child process, then we let both parent and child process run for the first 5 seconds. After 5 seconds, parent process ends while child process, which **is orphaned** now keeps running. Pressing Ctr+C for SIGINT won't kill child process:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>   

#define DELAY_TIME 1

void sigint_handler(int signal_number){
	kill(getpid(), SIGKILL);
}

int main(int argc, char *argv[])  {
    signal(SIGINT, sigint_handler);
	int pid = fork();
	if (pid) {
        // Let child process and parent process run for the first 5 seconds
        sleep(DELAY_TIME*5);
        printf("Parent process ends, only child process runs\n");
    } else {
        int number;
        while (1){
		    printf("number: %d\n", number);
		    number += 1;
		    sleep(DELAY_TIME);
		}
    }
}
```
**Result**
```
username$hostname:~$./a.out
number: 0
number: 1
number: 2
number: 3
number: 4
Parent process ends, only child process runs
number: 5 # child process, which is orphaned now keeps running
username$hostname:~$ number: 6 # child process, which is orphaned now keeps running
number: 7
number: 8
^C # Ctr+C SIGINT won't stop child process
username$hostname:~$ ^C # Ctr+C SIGINT won't stop child process
username$hostname:~$ ^C # Ctr+C SIGINT won't stop child process
username$hostname:~$
number: 9 # Child process keeps running and can't be stopped
number: 10
...
```
# Implementation
* [Communication between parent and child processes using pipe](Communication%20between%20parent%20and%20child%20processes%20using%20pipe.md)
* [Signal for fork()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Signal%20for%20fork().md)
* [Variable inside forked process](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Variable%20inside%20forked%20process.md)
# Application

* [IPC with TCP socket](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/TCP#examples): 1 server communicates with multiple clients. Process cloning with ``fork()`` is used to create a new process for a file descriptor for each tcp_client every time a new connection is established.

