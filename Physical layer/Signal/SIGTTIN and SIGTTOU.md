# SIGTTIN
When a background job tries to read from its current terminal, **SIGTTIN** will be triggered
## Trigger SIGTTIN as the background job
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
## Can't trigger SIGTTIN when a foreground job starts the background job which wants to have SIGGTTIN
This ``foreground_job`` will start the ``sigttin.c`` program aboves as the background job and intends to have SIGGTTIN triggered when typing input to the current terminal
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

int main(){
    std::cout << "start\n";
    execPid("./child_process");
    std::cout << "end\n";
    while(1);
}
```
**Result**: There is no SIGTTIN triggered in this ``foreground_job`` program.

**Explain**: For **SIGTTIN** to be triggered, a background job must try to read from its current terminal, i.e it must try to read from its **parent process** as the [PID of this terminal is the PPID of this process/background process](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process#getpid-and-getppid).

However, [PPID of a background job isn't the PID of the process starting it and is also not the PID of the current running terminal](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Background%20job#ppid-of-a-background-job-isnt-the-pid-of-the-process-starting-it).

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
