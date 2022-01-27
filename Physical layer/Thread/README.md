## Fundamental concepts

``pthreads``: POSIX threads

Compile: ``gcc test.c -lpthread``

POSIX.1 specifies that various other attributes are distinct for each thread, including:
*  thread ID (the ``pthread_t`` data type)
*  signal mask (``pthread_sigmask()``)
*  the ``errno`` variable
*  alternate signal stack (``sigaltstack()``)
*  real-time scheduling policy and priority (``sched()``)

The following Linux-specific features are also per-thread:
* capabilities (command ``capabilities``)
* CPU affinity (command ``sched_setaffinity``)

``Thread ID``: Each of the threads in a process has a unique thread identifier (stored in the type ``pthread_t``).

### Flow

[Example: Create a thread to print out a string](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#example-1)

The flow of that example:

Execute thread 1 (``pthread_join()``) -> Perform program operation behind ``pthread_join()``.

If the thread is an infinite loop, the program operation behind ``pthread_join()`` can't be reached.