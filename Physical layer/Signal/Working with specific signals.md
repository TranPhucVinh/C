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
# SIGTTIN
When a background job tries to read from its current terminal, SIGTTIN will be triggered:

``sigttin.c``
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>   

#define TERMINAL "/dev/pts/0"

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
    if (signal_number == SIGTTIN) {
        int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal SIGTTIN is caught\n");
    	write(STDOUT_FILENO, displayed_string, sz); 
    }
}

int main() {
    signal(SIGTTIN, signal_handler);
	int fd = open(TERMINAL, O_RDWR);
	if (fd > 0){
        printf("open %s successfully\n", TERMINAL);
        char buffer[10];
        bzero(buffer, sizeof(buffer));//Empty the previously entered buffer
        read(fd, buffer, sizeof(buffer));
	} else printf("Unable to open\n");
}
```
Running ``./sigttin&`` in the terminal will result in ``Signal SIGTTIN is caught`` is printed out infinitely.
# SIGTTOU
SIGTTOU is generated when a process in a background job attempts to write to the terminal and the TOSTOP output mode is set. [termios.h](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/README.md#termiosh) functions ``tcgetattr()`` and ``tcsetattr()`` are required to set ``TOSTOP`` flag:
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>   
#include <termios.h>
#include <errno.h> 

#define TERMINAL "/dev/pts/1"

struct termios tty;

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
    if (signal_number == SIGTTOU) {
        int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal SIGTTOU is caught\n");
    	write(STDOUT_FILENO, displayed_string, sz); 
    }
}

int main() {
    signal(SIGTTOU, signal_handler);
	int fd = open(TERMINAL, O_RDWR);
	if (fd > 0){
        printf("open %s successfully\n", TERMINAL);

		// Read in existing settings, and handle any error
		if(tcgetattr(fd, &tty) != 0) {
			printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		tty.c_iflag |= TOSTOP;

		// Save tty settings, also checking for error
		if (tcsetattr(fd, TCSANOW, &tty) != 0) {
			printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		char hw[] = "Hello, World !";
        write(fd, hw, sizeof(hw));
	} else printf("Unable to open\n");
}
```
