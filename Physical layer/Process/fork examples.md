### fork execution

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
Running child process inside ``while(1)`` loop:

```c
#include <stdio.h>
#include <unistd.h>

#define DELAY_TIME 1000000
int number;
int main(int argc, char *argv[])  {
	int pid = fork();
	if (!pid) {
        while (1){
            printf("number: %d\n", number);
            number += 1;
            usleep(DELAY_TIME);
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
```

**Running multiple fork()**
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