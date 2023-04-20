# Fundamental concepts

In computer science, a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is typically a part of the operating system.

Threads implemented in Unix are POSIX threads.

``pthreads`` is C POSIX threads library.

Compile: ``gcc test.c -lpthread``

## Create a thread to print out a string

```c
#include <stdio.h>
#include <pthread.h>

void *thread_func(void *ptr);

int main()
{  
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, thread_func, NULL);
	pthread_join(thread_id, NULL);
	printf("thread_1 finish executing\n");
    printf("Thread ID %lu\n", thread_id);
}

void *thread_func(void *ptr){
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

Program's flow::

* **Step 1**: Execute thread 1 (``pthread_join()``)
* **Step 2**: Perform program operation behind ``pthread_join()``

If the thread is an infinite loop, the program operation behind ``pthread_join()`` can't be reached.

When not using ``pthread_join()``:

```c
int main()
{  
	pthread_t thread_1;

	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	printf("thread_1 finish executing\n");
}
```

**Result**

```
thread_1 finish executing
```

We expect ``Hello, World !`` in ``func_thread_1()`` to be printed out but it is not. That happens as ``main()`` ends its life cycle before ``func_thread_1()`` is executed. To solve that problem, use ``pthread_join()``.

## Fundamental concepts examples

[Fundamental concepts examples](Fundamental%20concepts%20examples.md) includes:

* [Get the parameter of the thread by passing a variable](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#get-the-parameter-of-the-thread-by-passing-a-variable)
* [Get return from threads and store to a variable in single thread and multiple threads](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#get-return-from-threads-and-store-to-a-variable)
* [Enter value for struct member using thread](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#enter-value-for-struct-member-using-thread)
* Using global variable to share values between 2 threads: [share_global_variables_between_2_threads.c](share_global_variables_between_2_threads.c)

# [Race condition](Race%20condition)

A race condition is a situation where the result produced by two processes (or threads) operating on shared resources depends in an unexpected way on the relative order in which the processes gain access to the CPU(s).

When 2 threads trying to access a resource, data race might be happen if the racing between the 2 tasks to that the resource happens in a long time, like being inside an iteration loop for too long (with more than 10000 times).

[Race condition document](Race%20condition) includes:
* [One thread function handler to increase a share value](Race%20condition/README.md#one-thread-function-handler-to-increase-a-share-value)
* [One thread function handler to increase and decrease a shared value](Race%20condition/README.md#one-thread-function-handler-to-increase-and-decrease-a-shared-value)
* [Accessing a shared variable between 2 thread function handlers](Race%20condition/README.md#accessing-a-shared-variable-between-2-thread-function-handlers)
* [Semaphore](Race%20condition/Semaphore.md)
* [Mutex](Race%20condition/Mutex.md)

# [API](API.md)
* [pthread_create()](API.md#pthread_create)
* [pthread_join()](API.md#pthread_join)
* [pthread_self()](API.md#pthread_self)

# Application

## Use multiple threads for calculation

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

# Other concepts

## Spin lock

If a resource is locked, a thread that wants to access that resource may repetitively check whether the resource is available. During that time, the thread may loop and check the resource without doing any useful work. Suck a lock is termed as spin lock.
