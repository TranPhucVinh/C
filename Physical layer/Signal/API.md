# kill()

```c
int kill(pid_t pid, int sig);
```
Send signal (``sig``) to a process specified by ``pid``.
If ``pid=0``, ``sig`` is sent to every process in the process group of the calling process.

**Return**: On success (at least one signal was sent), ``0`` is returned.  On error, ``-1`` is returned, and ``errno`` is set to indicate the error.

# signal()

``signal()``: sets a function to handle signal

```c
sighandler_t signal(int signum, sighandler_t signal_handler);
```

* ``signum``: The signal number to which a handling function is set.
* ``signal_handler``: The ``signal_handler`` function has prototype

```c
void signal_handler(int signal_number);
```

``signal_handler()`` runs asynchronously, it can interrupt the program at any point. Some functions are listed a async-signal-safe, which includes ``write()``, not ``printf()``. So using ``printf()`` is not recommended and may cause the program with signal to crash in some case.

# sigaction()

```c
int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);
```

* ``act``: If act is non-NULL, the new action for signal ``signum`` is installed from ``act``.
* ``oldact``: If oldact is non-NULL, the previous action is saved in ``oldact``.

```c
struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
};
```

* ``sa_mask``: A mask of signals which should be blocked
* ``sa_flags``: A set of flags which modify the behavior of the signal.

Data type ``sigset_t`` represents a set of signals. Check [process signal mask document](Process%20signal%20mask.md) for implementation to form ``sigset_t`` object.

Signal handler function can be used with ``sa_sigaction`` to handle parameters:

To use ``sa_sigaction`` and get the parameter successfully in ``sa_sigaction`` function handler, flag ``SA_SIGINFO`` must be used.

```c

/*
    ucontext: This is a pointer to a ucontext_t structure, cast to
              void *.  The structure pointed to by this field contains
              signal context information that was saved on the user-
              space stack by the kernel
*/
void signal_action_handler(int signal_number, siginfo_t *siginfo, void *ucontext){
	//Operations go here
}

int main(){
	struct sigaction sa;
    sa.sa_sigaction = &signal_action_handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, NULL);
}
```

The ``siginfo_t`` data type is a structure with many members inside. ``union sigval si_value`` is included for ``sigqueue sigval``

```c
siginfo_t {
	int      si_signo;     /* Signal number */
	int      si_errno;     /* An errno value */

	//Other mmembers are ommitted

	pid_t    si_pid;       /* Sending process ID */
	uid_t    si_uid;       /* Real user ID of sending process */
	union sigval si_value; /* Signal value */
	int      si_int;       /* POSIX.1b signal */
	void    *si_ptr;       /* POSIX.1b signal */
	
	//Other mmembers are ommitted
}
```

# sigqueue()

Queue a signal and data to a process

```c
int sigqueue(pid_t pid, int sig, const union sigval value);
```

```c
union sigval {
	int   sival_int;
	void *sival_ptr;
};
```

``sigqueue()`` can be used to send parameter to other process that handles the signal.

# sigprocmask()

```c
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);
```
``sigprocmask()`` is used to fetch and/or change the signal mask of the calling thread.

``oldset``: If oldset is **non-NULL**, the previous value of the signal mask is stored in oldset

``set``: If ``set`` is **NULL**, then the signal mask is unchanged (i.e., ``how`` is ignored), but the current value of the signal mask is nevertheless returned in oldset (if it is **not NULL**).

``how``:

* ``SIG_BLOCK``: Block ``sigset_t *restrict set`` signals
* ``SIG_UNBLOCK``: Unblock ``sigset_t *restrict set`` signals
* ``SIG_SETMASK``: Working like ``SIG_BLOCK`` if ``oldset`` is not used
# sigpending() and sigismember()
```c
#include <signal.h>
int sigpending(sigset_t *set);
int sigismember (const sigset_t *set, int signum);
```
``sigpending()`` will set the list of pending/masking into its ``sigset_t *set``.

``sigismember()`` tests whether the signal ``signum`` is a member of the ``sigset_t *set``. It returns ``1`` if the signal is in the set, ``0`` if not, and ``-1`` if there is an error.

Check [process signal mask document](Process%20signal%20mask.md#sigpending-and-sigismember) for implementation of ``sigpending()`` and ``sigismember()`` inside ``sigprocmask()`` when a signal is masked.
# struct sigevent()
``struct sigevent``, which is **only used as the argument of an API, is used by various APIs to describe the way a process is to be notified about an event, e.g in [mq_notify()]() when a new message is sent into the POSIX message queue.

```c
struct sigevent {
    int    sigev_notify;  /* Notification method */
    int    sigev_signo;   /* Notification signal */
    union sigval sigev_value; /* Data passed with notification */
    void (*sigev_notify_function)(union sigval); /* Function used for thread notification (SIGEV_THREAD) */
    void  *sigev_notify_attributes; /* Attributes for notification thread (SIGEV_THREAD) */
    pid_t  sigev_notify_thread_id; /* ID of thread to signal (SIGEV_THREAD_ID); Linux-specific */
};
```
* ``sigev_notify`` takes those value:
	* ``SIGEV_NONE``: don't do anything when the event occurs
 	* ``SIGEV_SIGNAL``: Notify the process by sending the signal specified in ``sigev_signo``
	* ``SIGEV_THREAD``: Notify the process by invoking ``sigev_notify_function`` "as if" it were the start function of a new thread
# pause()
```c
int pause(void);
```
pause() will 
* Pause/suspend the current process until the specific signal subscribed in that process is received
* Immediately terminate the current process if the non-subscribe signal is received

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
    while(1){
        pause();
        printf("Finish execution\n");
    }
}
```
With ``kill -USR1 1433`` (where ``1433`` is the PID of that ``a.out``) result:

```
$ ./a.out
Signal 10 is caught
Finish execution
// Keep waiting as inside while(1) with pause()
```
Then ``kill -USR2 1433``, ``a.out`` will stop immediate with result:
```
User defined signal 2
```
When no signals are subscribed like this program, ``a.out`` will stop immediately when receiving any signal sent to it.
```c
int main(){ 
    while(1){
        pause();
        printf("Finish execution\n");
    }
}
```
