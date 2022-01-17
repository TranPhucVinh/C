# Fundamental concepts

A process is an instance of a program in execution. We called this an ‘instance of a program’, because if the same program is run lets say 10 times then there will be 10 corresponding processes. A process execution includes one or many threads. It contains the program code and its activity. Depending on the operating system (OS), a process may be made up of multiple threads of execution that execute instructions concurrently.

A C compile program (``a.out``) program will run as a process and can be listed in ``ps`` and has the ``PPID`` (parent process ID) of that terminal.

Each process has a parent - the process that created it. The parent of each process has its own parent, and so on, going all the way back to process 1, ``init``, the ancestor of all processes. This “family tree” can be viewed using the ``pstree()`` command.

### Process ID

The Linux kernel limits process IDs to being less than or equal to ``32,767``. When a new process is created, it is assigned the next sequentially available process ID. Each time the limit of ``32,767`` is reached, the kernel resets its process ID counter so that process IDs are assigned starting from low integer values.

Once it has reached ``32,767``, the process ID counter is reset to 300, rather than 1. This is done because many low-numbered process IDs are in permanent use by system processes and daemons, and thus time would be wasted searching for an unused process ID in this range.

# API

[API.md](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/API.md)