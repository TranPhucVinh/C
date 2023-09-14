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
When mapping memory with mmap() for an unnamed semaphore with the wrong length, SIGBUS is triggered:

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/shm.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>   

#define SHM_NAME    "/SHARED_MEMORY"
#define BASE_ADDR   0   //No specific base address to set in shared memory

int     *ptr;
sem_t   *sem_ptr;

void signal_handler(int signal_number);

int main(){
    signal(SIGBUS, signal_handler);
    int shm_fd = shm_open(SHM_NAME, O_CREAT|O_RDWR, 0777);
    if (shm_fd < 0) {
		printf("Unable to open %s\n", SHM_NAME);
		return 0;
	}
	printf("Shared memory object %s is opened successfully with fd %d\n", SHM_NAME, shm_fd);

    sem_ptr = mmap(NULL, sizeof(sem_t), PROT_WRITE, MAP_SHARED, shm_fd, BASE_ADDR);
    if (sem_ptr < 0){
        printf("mmap() for semaphore fails\n");
        return 0;
    }
	printf("Semaphore mmap() successfully\n");

	// This sem_init() triggers SIGBUS
    if (sem_init(sem_ptr, 1, 1) == -1 ){
        printf("Unable to init POSIX semaphore\n");
        return 0;
    }
    printf("Init POSIX semaphore successfully\n");
}

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "SIGBUS: Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}
```
Check the [sem_init implementation for process race condition: Two processes increase the value of a POSIX shared memory region](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Race%20condition/2_processes_increase_a_posix_shared_mem_value_sem_init.c) for the correct way of mapping memory for unnamed semaphore.
