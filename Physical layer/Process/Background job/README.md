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
``foreground_job.c``: Start the background job by [& (ampersand operator)](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Operators.md#-control-operator)
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

