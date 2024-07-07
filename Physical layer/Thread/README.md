# Fundamental concepts

In computer science, a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is typically a part of the operating system and can be thought as a unit of execution within a process.

The implementation of threads and processes differs between systems, like in MCU and OS, but in most cases a thread is a component of a process. Multiple threads can exist within one process, executing concurrently and sharing resources such as memory.

A thread has its own:
* Thread ID
* Stack and local variables

Threads implemented in Unix are POSIX threads. ``pthreads`` is C POSIX threads library.

Compile: ``gcc test.c -lpthread``

## Create a thread to print out a string

```c
#include <stdio.h>
#include <pthread.h>

void *thread_func(void *ptr);

int main() {  
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, thread_func, NULL);
	pthread_join(thread_id, NULL);
	printf("thread_1 finish executing\n");
    printf("Thread ID %lu\n", thread_id);
}

void *thread_func(void *ptr) {
	printf("Hello, World !\n");
    printf("Thread ID %lu\n", pthread_self());
}
```

**Result**

```
Hello, World !
Thread ID 140053257754368
thread_1 finish executing
Thread ID 140053257754368
```

## Program's flow

* **Step 1**: Execute thread 1. [pthread_join()](API.md#pthread_join) will make the current process to wait for all operations in thread 1 to finish.
* **Step 2**: Perform program operation after thread 1 finishes executing, i.e perform program operation behind [pthread_join()](API.md#pthread_join)

If the thread is an infinite loop, the program operation behind [pthread_join()](API.md#pthread_join) can't be reached.

When not using [pthread_join()](API.md#pthread_join):

```c
int main() {  
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	printf("thread_1 finish executing\n");
}
```

**Result**

```
thread_1 finish executing
```

We expect ``Hello, World !`` in ``func_thread_1()`` to be printed out but it is not. That happens as ``main()`` ends its life cycle before ``func_thread_1()`` is executed. To solve that problem without using [pthread_join()](API.md#pthread_join), we can put ``sleep(1)``:
```c
int main() {
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	printf("thread_1 finish executing\n");
	sleep(1);
}
```
**Note for using [pthread_join()](API.md#pthread_join)**: **pthread_join() doesn't start, create or join the specified thread to the current process** as **pthread_create()** has already done that. **pthread_join()** just simply waits for the thread it specified to finish execution. [Using pthread_join() for the thread included while(1) loop will block the program](API.md#pthread_join-will-block-the-process-if-the-thread-it-specifies-included-while1).

## Fundamental concepts examples

[Fundamental concepts examples](Documents/Fundamental%20concepts%20examples.md) includes:

* [Get the parameter of the thread by passing a variable](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#get-the-parameter-of-the-thread-by-passing-a-variable)
* [Get return from threads and store to a variable in single thread and multiple threads](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#get-return-from-threads-and-store-to-a-variable)
* [Enter value for struct member using thread](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#enter-value-for-struct-member-using-thread)

# Inter-task communication

## [Using global variable to share values between 2 threads](src/share_global_variables_between_2_threads.c)
## pthread doesn't have API for suspending and resuming thread

**Suspend a thread when reaching a specific value then resume that thread by another one** can be implemented by
* [mutex with condition variable](Documents/Mutex.md): [suspend a thread when reaching a specific value then resume that thread by another thread](src/suspend_and_resume_threads_by_mutex_and_cond.c)
* [Semaphore](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/suspend_and_resume_threads_by_semaphore.c)
* [Thread barrier](src/suspend_and_resume_threads_by_thread_barrier.c)

For efficient implementation, suspend and resume threads must be implemented with OOP. Check [the corresponding document in CPP](https://github.com/TranPhucVinh/Cplusplus/tree/master/Physical%20layer/Thread#suspend-and-resume-threads) for that implementation.

## [Race condition](Race%20condition)

A race condition is a situation where the result produced by two processes (or threads) operating on shared resources depends in an unexpected way on the relative order in which the processes gain access to the CPU(s).

When 2 threads try to access a resource, data race might happen if the racing between the 2 tasks to that the resource happens in a long time, like being inside an iteration loop for too long (with more than 10000 times).

[Race condition document](Race%20condition) includes:
* [One thread function handler to increase a shared value](Documents/Race%20condition.md#one-thread-function-handler-to-increase-a-shared-value)
* [One thread function handler to increase and decrease a shared value](Race%20condition/README.md#one-thread-function-handler-to-increase-and-decrease-a-shared-value)
* [Accessing a shared variable between 2 thread function handlers](Race%20condition/README.md#accessing-a-shared-variable-between-2-thread-function-handlers)
* [Semaphore](Documents/Semaphore.md)
* [Mutex](Documents/Mutex.md)
# [Thread barrier](Thread%20barrier.md)
# Concurrency and parallelism

If 2 threads are doing work in parallel, it means they're doing their works at exactly the same time. **Parallelism** typically requires some kind of hardware support like multiple core or coprocessor.

If a machine has 1 core, it can only runs 1 thread at a time. In order to run multithread as **concurrent**, system has to run one thread for a short amount of time then switch to the other and run that one for a short amount time, then keeps switching back and forth. The switching mechanism will be quick enough that the users don't notice the switching.
# [API](API)
* Thread creation
* Inter-task communication
# Application

## Use multiple threads for calculation

[Use 2 threads to calculate the sum from 1 to 2147483646](src/sum_from_1_to_n.c). This example will take 3 seconds to perform while [the raw function call](https://github.com/TranPhucVinh/C/blob/master/Algorithms/sum_from_1_to_n.c) will take 5 seconds to execute.

Using 3 threads will cause overflow error when compiling:

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
## [Multithread HTTP server built on TCP API](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/HTTP%20server#multithread-http-server-built-on-tcp-api)
