# system()

Run embedded Unix or Windows commands in ``C`` source code

```c
#include <stdlib.h>

main() {
	system("ls"); //Run ls command
}
```

On Windows, the ``a.exe`` of this file will run normally in Git Bash and will result in error ``command not found`` in Command Prompt.

``system("dir");`` will run properly in Command prompt.
## Use system() to start a process which includes a while(1) loop in the background
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
# popen() and pclose()

The ``popen()`` function opens a process by creating a pipe, forking, and invoking the shell.

```c
FILE *popen(const char *command, const char *type);
```

The ``command`` argument is a pointer to a null-terminated string containing a shell command line.  This command is passed to ``/bin/sh``, then interpretation, and finally is performed by the shell.

``pclose()`` will close the pipe opened by ``popen()``.

```c
int pclose(FILE *stream);
``` 

``ls`` command

```c
#include <stdio.h>

#define ELEMENT_NUMBERS 1
#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];


int main(){
    FILE* pipe = popen("ls", "r");
    fread(buffer, BUFFER_SIZE, ELEMENT_NUMBERS, pipe);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
    printf("%s\n", buffer);
    pclose(pipe);
}
```

``rm`` command:

```c
FILE* pipe = popen("rm a.out", "r");
pclose(pipe);
```
