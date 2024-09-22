# getpid() and getppid()

```c
#include <unistd.h>

printf("PID %d\n", getpid());
printf("Parent PID or PPID %d\n", getppid());
```
``getpid()`` returns the process ID of the calling process (this is often used by routines that generate unique temporary filenames)

``getppid()`` returns the **PPID**, i.e **ID of the parent process**, the process that create the child process. When running a process inside a terminal, its PPID is the PID of this terminal.
# ftok()
```c
key_t ftok(const char *pathname, int id);
```
Convert a ``pathname`` and an ``id`` to a System V IPC key to be used for [msgget()](https://github.com/TranPhucVinh/C/blob/5404146d439518f91248821a945bf33ec95425b2/Physical%20layer/Process/Message%20queue/README.md#msgget), **semget()**, or [shmget()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Shared%20memory/README.md#shmget).
# exit()

Exit the current program (as a process) and return value ``status`` for the further process.

```c
void exit(int status) 
```

**Example**

```c
#include <stdio.h>
#include <stdlib.h> // For exit()

int main(){
	for(int i=0;i<10;i++){
		printf("number: %d \n", i);
		exit(0);
	}
}
```

**Result** ``number: 0 ``

This example program runs on both Windows and Linux.
# ps

``ps``: Report process status

``-e``: List all process on the system

``-f``: Full-format listing

E.g: ``ps -e | grep $PPID``: Find the parent process of the current running shell

``-o``: User-defined format.

E.g: ``ps -o ppid= -p 9801``: Find the parent process of process ``9801``

Running ``ps`` return:

```
  PID TTY          TIME CMD
16965 pts/19   00:00:00 bash
18739 pts/19   00:00:00 ps
```

``ps ax | grep firefox``: Return nothing in Git Bash Windows

# pstree

``pstree`` will view the tree of running process

View process tree of a specific proccess, like ``2029``:  ``pstree -p 2029``

# pgrep and pkill 

``pgrep``, ``pkill``: look  up  or signal processes based on name and other attributes

``pkill a.out``: Kill the process named ``a.out`` (listed by ``ps`` command)
# netstat

``netstat -tulpn``: Find out which process is listening upon a port

# exec

``exec`` command executes a command from the bash itself. 

Whenever we run any command in a Bash shell, a subshell is created by default, and a new child process is spawned (forked) to execute the command. When using ``exec``, however, the command following exec replaces the current shell. This means no subshell is created and the current process is replaced with this new command.

E.g: When starting terminal 1, it will have a PID, e.g ``9001``. In terminal 2, like the result below, that PID can be listed out with ``ps aux``:

```
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
tranphu+  9001  0.0  0.0  24288  5256 pts/18   Ss   21:36   0:00 bash
```

With any command we do in terminal 1, like ``sleep 10``, its command ``bash`` is still unchanged.

However, if we use ``exec sleep 10`` in terminal 1, then in terminal 2 ``ps aux``, the result will be:

```
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
tranphu+  9001  0.0  0.0  24288  5256 pts/18   Ss   21:36   0:00 sleep 10
```

That happens as no subshell is created in terminal 1, it now is replaced by command ``sleep`` instead ``bash``.

With ``exec sleep 10``, after 10 seconds of sleep, the current shell will be closed as its execution has completed.

If ``exec`` is inside ``test.sh`` like this:

```sh
exec ls
```

Then running ``test.sh`` won't exit the current running shell. That happen as running ``test.sh`` will create a new shell in the current running terminal.

To stop quitting the current terminal when running ``exec ls``, add ``bash`` before it:

```sh
$ bash
$ exec ls
```

That happen as running ``bash``  will create a new shell in the current running terminal.

# $! for PID of background process

``$!`` returns the PID of the latest program run in the background

```sh
username@hostname:~$ ls&
[1] 466
username@hostname:~$ file_1.txt file_2.txt
^C
[1]+  Done                    ls --color=auto
username@hostname:~$ echo $!
466
```
