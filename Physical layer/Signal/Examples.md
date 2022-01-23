### Example 1: SIGUSR2 signal

Print out a string if signal ``12`` (``SIGUSR2``) is sent to PID of this process

Using ``signal()``:

```c
#include <stdio.h>
#include <signal.h>   

void signal_handler(int signalNumber){
	printf("You have entered signal number: %d\n", signalNumber); 
}

int main(){ 
	signal(SIGUSR2, signal_handler);
	while(1);//Start an infinite loop and handle with signal
}
```

Using ``sigaction()``:

```c
void signal_handler(int signal_number){
	printf("You have entered signal number: %d\n", signal_number); 
}

int main(){ 
    struct sigaction sa;
    sa.sa_handler = &signal_handler;

    sigaction(SIGUSR2, &sa, NULL);
	while(1);//Start an infinite loop and handle with signal
}
```

In other terminal

Run ``ps aux|grep a.out`` to find PID of ``a.out``. E.g PID of ``a.out`` is ``12976``

Run ``kill -12 12976``

To send signal to that ``a.out`` by other C process, using ``kill()``:

```c
#include <stdio.h>
#include <signal.h>   

#define PID 19499

int main(){ 
    kill(PID, SIGUSR2);
}
```

Using ``Ctr+Z`` for ``SIGTSTP`` signal:

```c
void signal_handler(int signal_number){
	printf("You have entered signal number: %d\n", signal_number); 
}

int main(){ 
	signal(SIGTSTP, signal_handler);
	while(1);//Start an infinite loop and handle with signal
}
```

Then pressing ``Ctr+Z`` won't stop the process and just cause the program to simply print out the string ``You have entered signal number: 20``. That happen as ``Ctr+Z`` sends the suspend signal on most Linux terminals, so with the signal handler function the program won't stop execution on the terminal.

### Example 2: SIGKILL signal

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

### Example 3

Working with ``SIGWINCH`` signal: If changing the current terminal size by mouse, the size of the terminal is printed out.

```c
#include <stdio.h> 
#include <unistd.h>
#include <signal.h> 
#include <sys/ioctl.h>

void signal_handler(int signalNumber){
	if (signalNumber == SIGWINCH){
		struct winsize ws;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

		printf("rows: %d\n", ws.ws_row);
		printf("columns: %d\n", ws.ws_col);
	}
}

int main(){ 
	signal(SIGWINCH, signal_handler);
	while(1);
}
```
