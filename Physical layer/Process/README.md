# Fundamental concepts

* [Process cloning](Process%20cloning)
* [Inter-process communication]()

## Inter-process communication

* [pipe](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/pipe.md)
* [FIFO](../File%20IO/FIFO)
* Semaphore
* Message queue
* Shared memory
* [Socket](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/TCP)
* [Signal](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Signal)

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

# Examples

* Using pipe to communicate between parent and child process: [pipe examples](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/pipe%20examples.md)
* Using FIFO to communicate between 2 process: [FIFO example in File IO](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/FIFO.md#example-2)
