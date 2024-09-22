# Process definition

A process is an **instance of a program in execution**. We called this an ‘instance of a program’, because if the same program is run lets say 10 times then there will be 10 corresponding processes. A process execution includes one or many threads. It contains the program code and its activity. Depending on the operating system (OS), a process may be made up of multiple threads of execution that execute instructions concurrently.

A C compile program (**a.out**) program will run as a process and can be listed in ``ps`` and has the ``PPID`` (parent process ID) of that terminal.

Each process has a parent - the process that created it. The parent of each process has its own parent, and so on, going all the way back to **the process with PID 1**, named **init**, the ancestor of all processes. This “family tree” can be viewed using the ``pstree()`` command. Process **init** primarily responsible for starting and shutting down the system, as it's the first process invoked by the kernel.

# Process ID

In Linux 2.4 and earlier, the Linux kernel limits process IDs to being less than or equal to ``32,767``. the process ID limit of ``32,767`` is defined by the kernel constant ``PID_MAX``. With Linux 2.6, things change. While the default upper limit for process IDs remains ``32,767``, this limit is adjustable via the value in the Linux-specific ``/proc/sys/kernel/pid_max`` file (which is one greater than the maximum process ID).

When a new process is created, it is assigned the next sequentially available process ID. Each time the limit of ``32,767`` is reached, the kernel resets its process ID counter so that process IDs are assigned starting from low integer values. 

Once it has reached ``32,767``, the process ID counter is reset to 300, rather than 1. This is done because many low-numbered process IDs are in permanent use by system processes and daemons, and thus time would be wasted searching for an unused process ID in this range.

# Stages of a Linux process

* Waiting: Process wait for resource
* Running: Process is currently being executed
* Stopped: Process is stopped after successful execution
* Zombie: Process has stopped but still active in the process table

# View process information

Information of a process can be viewed in file ``/proc/PID/status``. E.g: 

View status of process ``16965``: ``cat /proc/16965/status``

``echo $$``: Print out the ``PID`` of the current running shell

``echo $PPID`` or ``ps -e | grep $PPID``: Print out the parent process of the current running shell
# Background process

A background process is a computer process that runs behind the scenes (i.e., in the background) and without user intervention. Typical tasks for these processes include logging, system monitoring, scheduling, and user notification. The background process usually is a [child process](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Process%20cloning) created by a control process for processing a computing task. 

**Daemon**: A daemon is a computer program that runs as a background process, rather than being under the direct control of an interactive user.

# Jobs

A job is a process that the shell manages. Each job is assigned a sequential job ID. Because a job is a process, each job has an associated PID. There are three types of job statuses:

1. **Foreground**: When you enter a command in a terminal window, the command occupies that terminal window until it completes. This is a foreground job.
2. **Background**: When you enter use [ampersand symbol (&)](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Operators.md#-control-operator) at the end of a command line, the command runs without occupying the terminal window.
3. **Stopped**: If you press Control + Z for a foreground job, or enter the stop command for a background job, the job stops. 

To run a job **in the background**, 
``jobs`` command will list the jobs that are currently running or suspended in the background.

E.g:

```
username$hostname:~/pwd$$ jobs
[1]-  Stopped                 ./a.out
[2]+  Stopped                 ./a.out
```

``fg`` brings a background job to the foreground.

E.g:

```sh
fg % 1 #job ID 1 from [1] of ./a.out
```

``Control+Z`` keys and ``bg`` command bring a job to the background.

E.g:

```sh
bg % 1
```
