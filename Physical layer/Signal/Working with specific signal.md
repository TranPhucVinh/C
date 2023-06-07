# SIGHUP, SIGUSR1, SIGUSR2 can stop a process without signal_handler() required
An infinite running process like this can be stopped by SIGHUP, SIGUSR1, SIGUSR2
```c
int main(void)
{
	while(1)
	{
        printf("Hello, World !\n");
        sleep(1);
	}
}
```
[]()
# SIGUSR1 and SIGUSR2

Print out a string if multiple signals like ``10`` (``SIGUSR1``) and ``12`` (``SIGUSR2``) are sent to PID of this process

Using ``signal()``:

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>   

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while(1);//Start an infinite loop and handle with signal
}
```

Using ``sigaction()``:

```c
void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
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

Run ``kill -12 12976`` or ``kill -USR2``

To send signal to that ``a.out`` by other C process, using ``kill()``:

```c
#include <stdio.h>
#include <signal.h>   

#define PID 19499

int main(){ 
    kill(PID, SIGUSR2);
}
```

# SIGTSTP and SIGINT

Using ``Ctr+Z`` for ``SIGTSTP`` signal:

```c
void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
	signal(SIGTSTP, signal_handler);
	while(1);//Start an infinite loop and handle with signal
}
```

Then pressing ``Ctr+Z`` won't stop the process and just cause the program to simply print out the string ``You have entered signal number: 20``. That happen as ``Ctr+Z`` sends the suspend signal on most Linux terminals, so with the signal handler function the program won't stop execution on the terminal.

The same behavior happen with ``Ctr+C`` as ``SIGINT``:

```
//Other operations like above
signal(SIGINT, signal_handler);
//Other operations like above
```
**Result**

```
^CYou have entered signal number: 2
^CYou have entered signal number: 2
^CYou have entered signal number: 2
```

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

# SIGWINCH

If changing the current terminal size by mouse, the size of the terminal is printed out.

```c
#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <sys/ioctl.h>

void signal_handler(int signalNumber){
    char displayed_string[50];
	bzero(displayed_string, 50);

	if (signalNumber == SIGWINCH){
		struct winsize ws;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

	        int sz = snprintf(displayed_string, sizeof(displayed_string), "rows: %d\ncolumns: %d\n", ws.ws_row, ws.ws_col);
        	write(STDOUT_FILENO, displayed_string, sz);
	}
}

int main(){ 
	signal(SIGWINCH, signal_handler);
	while(1);
}
```
# SIGFPE
Report SIGFPE when storing the divided-by-0 result into a variable:

```c
void div_by_zero(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught, divided by 0\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
	signal(SIGFPE, div_by_zero);
	sleep(5);
	int a = 5/0;
	return 0;
}
```
**Result**

```c
Signal 8 is caught, divided by 0
Signal 8 is caught, divided by 0
.... // Run forever
```
**Must**: The divided-by-0 result must be stored into a variable to trigger **SIGFPE**. If simply call ``5/0``, **SIGFPE** won't be triggered.