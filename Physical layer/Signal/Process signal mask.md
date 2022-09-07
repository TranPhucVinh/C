## Fundamental concepts

Masking signal is the process to mask a specific signal so that it won't cause any effect when the running process is handle the signal handler function of the main/expected signal.

## Implementations

### Masking signal

**Example**: Function ``signal_handler()`` is called when signal ``SIGUSR2`` is triggered and signal ``SIGTSTP`` (``Ctr+Z``) is masked so that it won't cause effect, i.e stopping the current running process, when ``signal_handler()`` is running.

**Source code**

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>   

sigset_t set;

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
    while(1){
        write(STDOUT_FILENO, "signal_handler() is triggered\n", 50);
        sleep(1);
    }
}

int main(){ 
    //Form sigset_t for sa_mask
    sigemptyset(&set);
    sigaddset(&set, SIGTSTP);//Mask Ctr+Z

    struct sigaction sa;
    sa.sa_handler = &signal_handler;
    sa.sa_mask = set;
    sigaction(SIGUSR2, &sa, NULL);
	while(1);//Start an infinite loop and handle with signal
}
```

Without ``sa.sa_mask = set``, when ``signal_handler()`` is running with ``while(1)`` loop ``signal_handler() is triggered``, if pressing ``Ctr+Z``, the process will stop.

``sa.sa_mask = set`` will disable ``Ctr+Z`` in this case.

To mask ``Ctr+Z`` by ``sigprocmask()``, simply replace ``sa.sa_mask = set`` by ``sigprocmask()``:

```c
//All operations like the example with sa.sa_mask
int main(){ 
    sigemptyset(&set);
    sigaddset(&set, SIGTSTP);//Mask Ctr+Z

    struct sigaction sa;
    sa.sa_handler = &signal_handler;

    sigprocmask(SIG_BLOCK, &set, NULL);
    sigaction(SIGUSR2, &sa, NULL);
	while(1);//Start an infinite loop and handle with signal
}
```

### Unmask signal with sigprocmask()

Masking features like the example above. When delay 20 seconds in ``signal_handler()``, unmask ``SIGTSTP`` ``Ctr+Z``:

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>   

sigset_t set;
int count = 0;

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
    while(1){
        write(STDOUT_FILENO, "signal_handler() is triggered\n", 50);
        sleep(1);
        count += 1;

        //If reach 20 seconds, unblock Ctr+Z
        if (count == 20) sigprocmask(SIG_UNBLOCK, &set, NULL);
    }
}

int main(){ 
    //Form sigset_t for sa_mask
    sigemptyset(&set);
    sigaddset(&set, SIGTSTP);//Mask Ctr+Z

    struct sigaction sa;
    sa.sa_handler = &signal_handler;

    sigprocmask(SIG_BLOCK, &set, NULL);
    sigaction(SIGUSR2, &sa, NULL);
	while(1);//Start an infinite loop and handle with signal
}
```
