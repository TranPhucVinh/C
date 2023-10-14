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
# [SIGTTIN](SIGTTIN%20and%20SIGTTOU.md#sigttin)
When a background job tries to read from its current terminal, SIGTTIN will be triggered
* [Trigger SIGTTIN as the background job]()
* [Can't trigger SIGTTIN when a foreground job starts the background job which wants to have SIGGTTIN]()

# [SIGTTOU](SIGTTIN%20and%20SIGTTOU.md#sigttou)
# SIGBUS
When mapping memory with mmap() for an unnamed semaphore with the wrong length, SIGBUS is triggered. Program: [trigger_sigbus_by_mmap.c](trigger_sigbus_by_mmap.c)

Check the [sem_init implementation for process race condition: Two processes increase the value of a POSIX shared memory region](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Race%20condition/2_processes_increase_a_posix_shared_mem_value_sem_init.c) for the correct way of mapping memory for unnamed semaphore.
# SIGSEGV
Write value to a string char pointer like this will trigger **SIGSEGV** signal:
```c
int main( int argc, char ** argv ) {
	signal(SIGSEGV, signal_handler);
  char *p = NULL ;
  *p = 'A' ;
}
```
As assigning value to the deallocated pointer result in unexpected behavior, this won't trigger SIGSEGV when running on WSL 20.04 and Xilinx Linux 5.15 board
```c
signal(SIGSEGV, signal_handler);
int *intPointer;

// This won't trigger SIGSEGV when running on WSL 20.04 and Xilinx Linux 5.15 board
intPointer = (int *) malloc(1);
*intPointer = 12;
	
printf("Int value before: %d \n", *intPointer); //12
free(intPointer);
printf("Int value after: %d \n", *intPointer); //0
*intPointer = 134;// Assign value to the deallocated pointer result in unexpected behavior
printf("Int value after: %d \n", *intPointer); //134
```
