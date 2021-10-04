### fork()

```c
int fork(void)
```

Clone the calling process, creating an exact copy. Return -1 for errors, 0 to the new process, and the process ID of the new process to the old process.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])  {
	int pid = fork();
	printf("Fork from PID: %d\n", pid);
}
```
```
Fork from PID: 29056
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