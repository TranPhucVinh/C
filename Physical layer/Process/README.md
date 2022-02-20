# Fundamental concepts

A process is an instance of a program in execution. We called this an ‘instance of a program’, because if the same program is run lets say 10 times then there will be 10 corresponding processes. A process execution includes one or many threads. It contains the program code and its activity. Depending on the operating system (OS), a process may be made up of multiple threads of execution that execute instructions concurrently.

A C compile program (``a.out``) program will run as a process and can be listed in ``ps`` and has the ``PPID`` (parent process ID) of that terminal.

Each process has a parent - the process that created it. The parent of each process has its own parent, and so on, going all the way back to process 1, ``init``, the ancestor of all processes. This “family tree” can be viewed using the ``pstree()`` command.

### Process ID

In Linux 2.4 and earlier, the Linux kernel limits process IDs to being less than or equal to ``32,767``. the process ID limit of ``32,767`` is defined by the kernel constant ``PID_MAX``. With Linux 2.6, things change. While the default upper limit for process IDs remains ``32,767``, this limit is adjustable via the value in the Linux-specific ``/proc/sys/kernel/pid_max`` file (which is one greater than the maximum process ID).

When a new process is created, it is assigned the next sequentially available process ID. Each time the limit of ``32,767`` is reached, the kernel resets its process ID counter so that process IDs are assigned starting from low integer values. 

Once it has reached ``32,767``, the process ID counter is reset to 300, rather than 1. This is done because many low-numbered process IDs are in permanent use by system processes and daemons, and thus time would be wasted searching for an unused process ID in this range.

### Stages of a Linux process

* Waiting: Process wait for resource
* Running: Process is currently being executed
* Stopped: Process is stopped after successful execution
* Zombie: Process has stopped but still active in the process table

## Jobs

A job is a process that the shell manages. Each job is assigned a sequential job ID. Because a job is a process, each job has an associated PID. There are three types of job statuses:

1. **Foreground**: When you enter a command in a terminal window, the command occupies that terminal window until it completes. This is a foreground job.
2. **Background**: When you enter an ampersand (``&``) symbol at the end of a command line, the command runs without occupying the terminal window.
3. **Stopped**: If you press Control + Z for a foreground job, or enter the stop command for a background job, the job stops. 

# API

[API.md](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/API.md)

# Examples

### fork

* [fork examples](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/fork%20examples.md)
* Using pipe to communicate between parent and child process: [pipe examples](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/pipe%20examples.md)
* Using FIFO to communicate between 2 process: [FIFO example in File IO](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/FIFO.md#example-2)
