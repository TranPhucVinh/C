# Use system() to start a process which includes a while(1) loop in the background
Process ``child_process`` include a ``while(1)`` loop which we want to start it inside ``parent_process`` but still want ``parent_process`` to keep running without stucking inside the ``while(1)`` loop of ``child_process``. The solution for that is to use ``&``  command to run a process in the background.

``child_process``
```c
#include <stdio.h>
#include <unistd.h>

int main(){
    while(1){
        printf("Child process\n");
        sleep(1);
    }
}
```

```cpp
#include <iostream>
#include <string>

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
}
```
**Result**:

```
username@hostname:~$ ./a.out
start
end
username@hostname:~$ Child process
Child process
Child process
Child process
...
```
After killing/stopping ``a.out``, ``child_process`` still runs in the background.
# Kill the infinite background process by signal
To kill ``child_process`` when killing ``parent_process``, use [signal](Signal) with ``SIGINT`` to catch ``Ctr+C`` in ``child_process``, ``SIGKILL`` to kill ``child_process``
``parent_process.c``
```c
#include <iostream>
#include <string>

using namespace std;

// Use system to run a process in the background
void execPid(const char* cmd)
{
    std::string localCommand(cmd);
    localCommand = localCommand + "&";
    system(localCommand.c_str());
    return;
}

int main(){
    cout << "start\n";
    execPid("./child_process");
    cout << "end\n";
    while(1); //Keep parent process running so that both parent and child process can be stopped by Ctr+C
}
```

``child_process.c``
```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>   

int pid;
void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
    kill(pid, SIGKILL);
}

int main(){
    pid = getpid();
    signal(SIGINT, signal_handler);
    while(1){
        sleep(1);
    }
}
```
# Run the infinite background process, get its PID then kills it by functions inside in the parent process

``startProcess()`` starts a process by its command and returns that process PID.

Run ``child_process`` which has ``while(1)`` loop in the background and kill it in parent process function:

```cpp
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>

#define PROCESS_NAME    "child_process"

int startProcess(const char* process_name);
void killProcess(int pid);

int main(){
	int pid = startProcess(PROCESS_NAME);
	printf("%d\n", pid);
	sleep(5);
	killProcess(pid);
}

int startProcess(const char* process_name){
    std::string start_process;
	int pid;
	start_process = "./" + std::string(process_name) + "& echo $! > txt.pid";
    if (system(start_process.c_str()) == -1) printf("Fail to start process in the background\n");
    else {
        char buffer[10];
        int fd = open("txt.pid", O_RDONLY);
        read(fd, buffer, 10);
        pid = strtol(buffer, NULL, 10);
    }
	return pid;
}

void killProcess(int pid){
	if (!kill(pid, SIGKILL)) printf("Kill process with PID %d successfully\n", pid);
	else printf("Fail to kill process with PID %d\n", pid);
}
```
# Stop child_process by SIGSTOP and continue it by SIGCONT
```c
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>

#define PROCESS_NAME    "child_process"

int startProcess(const char* process_name);

int main(){
   	int pid = startProcess(PROCESS_NAME);
	printf("%d\n", pid);
	sleep(5);// Sleep for 5 seconds to let child_process run for 5 seconds
    kill(pid, SIGSTOP);// Then stop/suspend child_process
    sleep(5);// Sleep for 5 seconds to let child_process stop/suspend for 5 seconds
    kill(pid, SIGCONT);// Then continue child_process
    sleep(5);// Sleep for 5 seconds to let child_process run for 5 seconds
    // Finally, kill child_process
    if (!kill(pid, SIGKILL)) printf("child_process with PID %d is killed\n", pid);
    else printf("Fail to kill child_process with PID %d\n", pid);
}

int startProcess(const char* process_name){
    std::string start_process;
	int pid;
	start_process = "./" + std::string(process_name) + "& echo $! > txt.pid";
    if (system(start_process.c_str()) == -1) printf("Fail to start process in the background\n");
    else {
        char buffer[10];
        int fd = open("txt.pid", O_RDONLY);
        read(fd, buffer, 10);
        pid = strtol(buffer, NULL, 10);
    }
	return pid;
}
```