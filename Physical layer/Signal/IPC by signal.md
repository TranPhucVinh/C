### sigqueue(): Sending signal and an int number from a process to other process

Send signal ``SIGUSR1`` and parameter with int value ``12`` to process with macro ``PID`` by using ``sigqueue()``

```c
#include <stdio.h>
#include <signal.h>   

#define PID 16367

union sigval value;

int main(){  
    value.sival_int = 12;
    sigqueue(PID, SIGUSR1, value);
}
```

Received signal ``SIGUSR1`` and the parameter sent from other process by using ``sa_sigaction`` from ``struct sigaction``:

```c
#include <stdio.h>
#include <unistd.h> //for getpid()
#include <signal.h>   
#include <string.h>   

/*
    ucontext: This is a pointer to a ucontext_t structure, cast to
              void *.  The structure pointed to by this field contains
              signal context information that was saved on the user-
              space stack by the kernel
*/
void signal_action_handler(int signal_number, siginfo_t *siginfo, void *ucontext){
    char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(  displayed_string,
                        sizeof(displayed_string),
                        "Signal number: %d, with parameter %d\n",
                        signal_number,
                        (siginfo->si_value).sival_int
                    );
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
    printf("PID %d\n", getpid());
    struct sigaction sa;
    sa.sa_sigaction = &signal_action_handler;

    /*
        To use sa_sigaction and get the parameter successfully in 
        sa_sigaction function handler, flag SA_SIGINFO must be used
    */
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, NULL);
	while(1);//Start an infinite loop and handle with signal
}
```
### sigqueue(): Can't send void* sival_ptr from a process to other process

Can't send a pointer from a process to other process by this method

```c
union sigval value;

int array[3] = {1, 2, 3};
//Or string: char str[] = "Hello, World !";

int main(){  
    value.sival_ptr = array;
    sigqueue(PID, SIGUSR1, value);
}
```

The receiver process in this case will just received the garbage value:

```c
void signal_action_handler(int signal_number, siginfo_t *siginfo, void *ucontext){
    char displayed_string[50];
	bzero(displayed_string, 50);
	
	int array[3];
	memcpy(array, (siginfo->si_value).sival_ptr, 3);
	int sz = snprintf(displayed_string, sizeof(displayed_string), "%d %d %d\n", array[0], array[1],array[2]);
	write(STDOUT_FILENO, displayed_string, sz); //Garbage value
}
```
That happen as the address which is sent from one process to the other via the value of ``sival_ptr`` is not valid in the receiving process, as the two processes do not share the same address space.

``void* sival_ptr`` can only be used inside the same process.
