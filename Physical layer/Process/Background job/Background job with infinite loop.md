# Kill the infinite background job by signal
To kill ``background_job`` when killing ``foreground_job``, use [signal](Signal) with ``SIGINT`` to catch ``Ctr+C`` in ``background_job``, ``SIGKILL`` to kill ``background_job``
``foreground_job.c``
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
    execPid("./background_job");
    cout << "end\n";
    while(1); //Keep parent process running so that both parent and child process can be stopped by Ctr+C
}
```

``background_job.c``
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
# Run the infinite background job, get its PID then kills it by functions inside in the parent process

``startProcess()`` starts a process by its command and returns that process PID.

Run ``background_job`` which has ``while(1)`` loop in the background and kill it in parent process function:

```cpp
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>

#define PROCESS_NAME    "background_job"

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
# Stop background_job by SIGSTOP and continue it by SIGCONT
```c
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>

#define PROCESS_NAME    "background_job"

int startProcess(const char* process_name);

int main(){
   	int pid = startProcess(PROCESS_NAME);
	printf("%d\n", pid);
	sleep(5);// Sleep for 5 seconds to let background_job run for 5 seconds
    kill(pid, SIGSTOP);// Then stop/suspend background_job
    sleep(5);// Sleep for 5 seconds to let background_job stop/suspend for 5 seconds
    kill(pid, SIGCONT);// Then continue background_job
    sleep(5);// Sleep for 5 seconds to let background_job run for 5 seconds
    // Finally, kill background_job
    if (!kill(pid, SIGKILL)) printf("background_job with PID %d is killed\n", pid);
    else printf("Fail to kill background_job with PID %d\n", pid);
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
