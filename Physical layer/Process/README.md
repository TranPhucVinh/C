# Fundamental concepts

* [Process cloning](Process%20cloning)
* [Inter-process communication](#inter-process-communication)

## Inter-process communication

Inter-process communication methods are:
* [pipe](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/pipe.md)
* [FIFO](../File%20IO/FIFO)
* Semaphore
* [Message queue](Message%20queue)
* [Shared memory](Shared%20memory)
* [Socket](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/TCP)
* [Signal](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Signal)

Command [ipcs](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Process/System%20V%20IPC.md#ipcs) is useful for checking the message queue, shared memory and semaphore information.

# RPC

In distributed computing, a **remote procedure call** (**RPC**) is when a computer program causes a procedure (subroutine) to execute in a different address space (commonly on another computer on a shared network), which is written as if it were a normal (local) procedure call. This is **a form of client–server interaction** (**caller** is **client**, **executor** is **server**), typically implemented via a request–response message-passing system. 

**RPCs are a form of inter-process communication (IPC)**, in that different processes have different address spaces: if on the same host machine, they have distinct virtual address spaces, even though the physical address space is the same; while if they are on different hosts, the physical address space is different.

# API

## getpid() and getppid()

```c
#include <unistd.h>

printf("PID %d\n", getpid());
printf("Parent PID %d\n", getppid());
```
``getpid()`` returns the process ID of the calling process (this is often used by routines that generate unique temporary filenames)

``getppid()`` returns the ID of the parent, the process that crate the child process.

## exit()

Exit the current program (as a process) and return value ``status`` for the further process.

```c
void exit(int status) 
```

**Example**

```c
#include <stdio.h>
#include <stdlib.h> // For exit()

int main(){
	for(int i=0;i<10;i++){
		printf("number: %d \n", i);
		exit(0);
	}
}
```

**Result** ``number: 0 ``

This example program runs on both Windows and Linux.
