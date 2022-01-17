### getpid() and getppid()

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