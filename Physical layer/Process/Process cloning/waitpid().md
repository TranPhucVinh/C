

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

``int options``:
* **WUNTRACED**: waitpid() returns when a child has stopped
* **WCONTINUED**: A stopped child has been resumed by delivery of **SIGCONT**

``int *status``: if ``status`` is not ``NULL``, ``waitpid()`` store status information in this pointer. This integer can be inspected with the following macros:

* ``WIFSTOPPED(status)``: returns ``true`` if the child process was stopped by delivery of a signal; this is only possible if the call was done using **WUNTRACED**
* ``WIFCONTINUED(status)``: returns ``true`` if the child process was resumed by delivery of **SIGCONT**

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>   
#include <sys/types.h>
#include <sys/wait.h>

#define DELAY_TIME 1

int main(int argc, char *argv[])  {
	int pid = fork();
	if (pid) {
        pid_t cpid;// Child process PID
        int status;

        cpid = waitpid(pid, NULL, WUNTRACED);
        if (cpid == -1) {
            perror("waitpid");
            return 0;
        } else printf("Child process with PID %d has been terminated\n", cpid);
    } else {
        while (1) sleep(DELAY_TIME);
    }
}
```
With PID=1502, when calling ``kill 1502`` or ``kill -SIGSTOP 1502``, result will be:
```
Child process with PID 1502 has been terminated
```
Using ``status`` to monitor the SIGSTOP and SIGCONT of child process:
```c
int main(int argc, char *argv[])  {
	int pid = fork();
	if (pid) {
        pid_t cpid;// Child process PID
        int status;
        // Start monitoring child process in parent process
        while(1){
            int status = 0;
            cpid = waitpid(pid, &status, WUNTRACED|WCONTINUED);
            if (cpid == -1) {
                perror("waitpid");
                return 0;
            } else {
                if (WIFSTOPPED(status)) printf("Child process with PID %d is stopped\n", cpid);
                else if (WIFCONTINUED(status)) printf("Child process with PID %d is continued\n", cpid);
            }
        }
    } else {
        while (1) sleep(DELAY_TIME);
    }
}
```
**Result**:
```sh
$ ./a.out
Child process with PID 1537 is stopped # kill -SIGSTOP 1532
Child process with PID 1537 is continued # kill -SIGCONT 1537
Child process with PID 1537 is stopped # kill -SIGSTOP 1537
Child process with PID 1537 is continued # kill -SIGCONT 1537
waitpid: No child processes # kill 1537
[2]+  Stopped (signal)           ./a.out
```