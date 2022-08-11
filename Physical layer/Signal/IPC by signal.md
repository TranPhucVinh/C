### Sending signal and parameter from a process to other process

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