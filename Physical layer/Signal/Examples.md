### Example 1

Print out a string if signal ``12`` (``SIGUSR2``) is sent to PID of this process

```c
#include <stdio.h>
#include <signal.h>   

void signal_handler(int signalNumber){
	if (signalNumber == SIGUSR2){
		printf("You have entered signal number: %d\n", signalNumber); 
	}
}

int main(){ 
	signal(SIGUSR2, signal_handler);
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

### Example 2

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
