# PPID of a [background job](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Process/README.md#jobs) isn't the PID of the process starting it
``background_job.c`` (Be not to confuse the background job with the [child process created by fork()](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Process%20cloning))
```c
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("PPID %d\n", getppid());
    while(1) sleep(1);
}
```
**foreground_job.c**: Background job **background_job** includes a ``while(1)`` loop which we want to start it inside **foreground_job** but still want **foreground_job** to keep running without stucking inside the ``while(1)`` loop of **foreground_job**. The solution for that is to use [& (ampersand operator)](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Operators.md#-control-operator) to start the background job **background_job**
```c
#include <iostream>
#include <string>
#include <unistd.h>

void execPid(const char* cmd)
{
  std::string localCommand(cmd);
  localCommand = localCommand + "&";
  system(localCommand.c_str());
  return;
}

int main(){
	printf("PID %d\n", getpid());
	std::cout << "start\n";
	execPid("./background_job");
	std::cout << "end\n";
}
```
**Result**: When running ``foreground_job``

```sh
username@hostname:~/$ ./foreground_job
PID 28487 # foreground_job PID
start
end
PPID 28269 # PPID of background_job, it's different from foreground_job PID
```
**PPID of the background job is also not the PID of the current running terminal**
```sh
username@hostname:~/$  ps
  PID TTY          TIME CMD 
28270 pts/2    00:00:00 bash   # This PID is different from foreground_job PID
28489 pts/2    00:00:00 background_job
28490 pts/2    00:00:00 ps  
```
When **background_job** includes the string display like this:
```c
int main(){
    while(1){
        printf("Background job\n");
        sleep(1);
    }
}
```

**Result** when running ``foreground_job``

```
username@hostname:~$ ./foreground_job
start
end
username@hostname:~$ Background job
Background job
Background job
Background job
...
```
After killing/stopping ``foreground_job``, ``background_job`` still runs in the background.
# [Kill the infinite background job by signal](Background%20job%20with%20infinite%20loop.md#kill-the-infinite-background-job-by-signal)
# [Run the infinite background job, get its PID then kills it by functions inside in the parent process](Background%20job%20with%20infinite%20loop.md#run-the-infinite-background-job-get-its-pid-then-kills-it-by-functions-inside-in-the-parent-process)
# [Stop background_job by SIGSTOP and continue it by SIGCONT](Background%20job%20with%20infinite%20loop.md#stop-background_job-by-sigstop-and-continue-it-by-sigcont)
