# SIGKILL

Self-terminated a process after printing from ``0`` to ``10``:

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>   

int pid;
int number;

int main(){  
    pid = getpid();
    while (1){
        printf("%d\n", number);
        if (number == 10) kill(pid, SIGKILL);
        else number += 1;
    }
}
```
