# SIGTTOU
SIGTTOU is generated when a process in a background job attempts to write to the terminal and the TOSTOP output mode is set. [termios.h](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/README.md#termiosh) functions ``tcgetattr()`` and ``tcsetattr()`` are required to set ``TOSTOP`` flag.

Program: [sigttou.c](../src/sigttou.c)

# SIGTTIN
When a background job tries to read from its current terminal, **SIGTTIN** will be triggered
## Trigger SIGTTIN as the background job
Program: [sigttin_triggered_as_background_job.c](../src/sigttin_triggered_as_background_job.c)

Running ``./sigttin&`` in the terminal will result in ``Signal SIGTTIN is caught`` is printed out infinitely.
## Can't trigger SIGTTIN when a foreground job starts the background job which wants to have SIGGTTIN
This ``foreground_job`` will start the ``sigttin_triggered_as_background_job.c`` program aboves as the background job and intends to have SIGGTTIN triggered when typing input to the current terminal
<details>
	
```c
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <signal.h>   

void execPid(const char* cmd)
{
  std::string localCommand(cmd);
  localCommand = localCommand + "&";
  system(localCommand.c_str());
  return;
}

int main() {
    std::cout << "start\n";
    execPid("./background_job");
    std::cout << "end\n";
    while(1);
}
```
</details>

**Result**: There is no SIGTTIN triggered in this ``foreground_job`` program.

**Explain**: For **SIGTTIN** to be triggered, a background job must try to read from its current terminal, i.e it must try to read from its **parent process** as the [PID of this terminal is the PPID of this process/background process](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process#getpid-and-getppid).

However, [PPID of a background job isn't the PID of the process starting it and is also not the PID of the current running terminal](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Background%20job#ppid-of-a-background-job-isnt-the-pid-of-the-process-starting-it).

This ``background_job.c`` program as the background job will try to open the file descriptor of its parent process in order to trigger SIGTTIN:

<details>
	
```c
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>  

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main() {
    int ppid = getppid();
    std::string path("/proc/");
	path += std::to_string(ppid) + "/fd/1";
	std::cout << path << std::endl;
    signal(SIGTTIN, signal_handler);
	int fd = open(path.c_str(), O_RDWR);
	if (fd > 0){
        printf("open successfully %d\n", fd);
		while(1){
				char buffer[10];
				read(fd, buffer, sizeof(buffer));
				sleep(1);
		}
	} else printf("Unable to open\n");
}
```
</details>

Then embedded/call this ``background_job`` inside ``foreground_job.c`` like before then start ``foreground_job`` by sudo (Must start ``foreground_job`` to open the fd of this background job's parent process) then SIGTTIN isn't triggered:
```sh
username@hostname:~/$ sudo ./foreground_job
/proc/29713/fd/1 # where 29713 is the PID of the background job
open successfully 3 
```
That happens because:
```sh
username@hostname:~/$ sudo ls -la /proc/29713/fd/1 
lrwx------ 1 root root 64 Aug 28 17:49 /proc/29713/fd/1 -> /dev/null # This fd points to /dev/null
```
While with the  ``background_job.c`` program as the background job above, when running ``./background_job&`` in the terminal will result in ``Signal SIGTTIN is caught`` printed infinitely, which has the identically result to [Trigger SIGTTIN as the background job](#trigger-sigttin-as-the-background-job):
```sh
username@hostname:~/$ sudo ./foreground_job
/proc/29714/fd/1 # where 29714 is the PID of the current terminal
open successfully 3
Signal 21 is caught
Signal 21 is caught
...//Infinitely
```
That happens because:
```sh
lrwx------ 1 vinhtran vinhtran 64 Aug 28 18:01 /proc/29714/fd/1 -> /dev/pts/5 # This fd points to the current terminal
```
# SIGSTOP and SIGCONT
## [Suspend a background process by SIGSTOP and continue it by SIGCONT from the parent process](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Background%20job/Background%20job%20with%20infinite%20loop.md#stop-background_job-by-sigstop-and-continue-it-by-sigcont)
