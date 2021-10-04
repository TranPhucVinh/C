### fork()

```c
int fork(void)
```

Clone the calling process, creating an exact copy. Return -1 for errors, 0 to the new process, and the process ID of the new process to the old process.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	printf("Before forking");
	int pid = fork();
	printf("Fork from PID: %d\n", pid);
}
```
```
Before forkingFork from PID: 1233
Before forkingFork from PID: 0
```
``Before forking`` is printed 2 times as it is not followed by a newline.

```c
int main(int argc, char *argv[])  {
	printf("Before forking\n");
	int pid = fork();
	printf("Fork from PID: %d\n", pid);
}
```
```
Before forking
Fork from PID: 1354
Fork from PID: 0
```

Running multiple ``fork()``
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

### wait()

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