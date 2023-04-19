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
To kill child process when killing ``a.out``, use [signal](Signal) with ``SIGINT`` to catch ``Ctr+C`` in ``child_process``, ``SIGKILL`` to kill ``child_process``
``parent_process``
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
    execPid("./header");
    cout << "end\n";
    while(1); //Keep parent process running so that both parent and child process can be stopped by Ctr+C
}
```

``child_process``
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
# Kill the infinite background process by functions inside in the parent process
Run child process which has while(1) loop in the background and kill it in parent process function:
```cpp
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>

#define PROCESS_NAME    "head"

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
