# Fundamental concepts

In computer science, a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is typically a part of the operating system.

## POSIX threads

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

* **Step 1**: Execute thread 1 (``pthread_join()``)
* **Step 2**: Perform program operation behind ``pthread_join()``

If the thread is an infinite loop, the program operation behind ``pthread_join()`` can't be reached.

## Inter-task communication

Using global variable to share values between 2 threads: [Check source code](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#using-global-variable-to-share-values-between-2-threads)

### Data race

When 2 threads trying to access a resource, data race might be happen if the racing between the 2 tasks to that the resource happens in a long time, like being inside an iteration loop for too long (with more than 10000 times):

```c
#include <stdio.h>
#include <pthread.h>

#define RANGE 10000

int share_value;

void *thread_function(void *ptr);

int main()
{  
	pthread_t thread_1, thread_2;
	int thread_1_return, thread_2_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_function, NULL);
   thread_2_return = pthread_create(&thread_2, NULL, thread_function, NULL);
	pthread_join(thread_1, NULL);
   pthread_join(thread_2, NULL);
   printf("share_value after executing 2 threads: %d\n", share_value);
}

void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) share_value++;
}
```
**Result**: ``share_value after executing 2 threads: 14736`` (Expected ``20000``)

With ``RANGE`` is less than ``10000``, that data race issue doesn't happen, as the time 2 tasks race to take the resouce ``share_value`` is short.

**Problem solved**

* [Using mutex](Mutex.md)
* [Using semaphore](Semaphore.md)

# API

ChecK [API](API.md) document.

# Examples

[Use 2 threads to calculate the sum from 1 to 2147483646](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/sum_from_1_to_n.c). This example will take 3 seconds to perform while [the raw function call](https://github.com/TranPhucVinh/C/blob/master/Introduction/Examples/sum_from_1_to_n.c) will take 5 seconds to execute.

Using 3 thread will cause overflow error when compiling:

```c
range_1.lower_range = 0;
range_1.upper_range = N/3;

range_2.lower_range = N/3 + 1;
range_2.upper_range = 2*N/3;

range_3.lower_range = 2*N/3 + 1;
range_3.upper_range = N;
```

Problem solve: 

```c
range_1.lower_range = 0;
range_1.upper_range = N/3;

range_2.lower_range = N/3 + 1;
range_2.upper_range = N/3 + N/3;

range_3.lower_range = N/3 + N/3 + 1;
range_3.upper_range = N;
```

Check [examples document](Examples.md) for other examples.

# Other concepts

### Spin lock

If a resource is locked, a thread that wants to access that resource may repetitively check whether the resource is available. During that time, the thread may loop and check the resource without doing any useful work. Suck a lock is termed as spin lock.
