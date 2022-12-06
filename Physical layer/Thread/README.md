# Fundamental concepts

In computer science, a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is typically a part of the operating system.

Threads implemented in Unix are POSIX threads.

``pthreads`` is C POSIX threads library.

Compile: ``gcc test.c -lpthread``

## Create a thread to print out a string

```c
#include <stdio.h>
#include <pthread.h>

void *func_thread_1(void *ptr);

int main()
{  
	pthread_t thread_1;

	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_join(thread_1, NULL);
	printf("thread_1 finish executing\n");
}

void *func_thread_1(void *ptr){
	printf("Hello, World !\n");
}
```

**Result**

```
Hello, World !
thread_1 finish executing
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

## Inter-task communication

Using global variable to share values between 2 threads: [Check source code](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#using-global-variable-to-share-values-between-2-threads)


### Race condition

When 2 threads trying to access a resource, data race might be happen if the racing between the 2 tasks to that the resource happens in a long time, like being inside an iteration loop for too long (with more than 10000 times). Check [race condition document](Race%20condition.md).

# API

### pthread_create()

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

The ``pthread_create()`` function starts a new thread in the calling process. The new thread starts execution by invoking ``start_routine()``; ``arg`` is passed as the sole argument of ``start_routine()``. It means, simply call ``pthread_create()`` will start executing the thread.

The ``attr`` argument points to a ``pthread_attr_t`` structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using ``pthread_attr_init()`` and related functions. If ``attr`` is ``NULL``, then the thread is created with default attributes.

Before returning, a successful call to ``pthread_create()`` stores the ID of the new thread in the buffer pointed to by ``thread``; this identifier is used to refer to the thread in subsequent calls to other pthreads functions.

On success, ``pthread_create()`` returns ``0``; on error, it returns an ``error number``, and the contents of ``*thread`` are ``undefined``.

### pthread_join()

```c
int pthread_join(pthread_t thread, void **retval);
```

The ``pthread_join()`` function waits for the thread specified by ``thread`` to terminate. If that thread has already terminated, then ``pthread_join()`` returns immediately. The thread specified by ``thread`` must be joinable.

If ``retval`` is not ``NULL``, then ``pthread_join()`` copies the exit status  of the target thread (i.e., the value that the target thread supplied to ``pthread_exit()``) into the location pointed to by ``retval``.  If the target thread was canceled, then ``PTHREAD_CANCELED`` is placed in the location pointed to by ``retval``.

On success, ``pthread_join()`` returns ``0``; on error, it returns an error number.

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

Check [examples document](Examples.md) for other examples.

# Other concepts

### Spin lock

If a resource is locked, a thread that wants to access that resource may repetitively check whether the resource is available. During that time, the thread may loop and check the resource without doing any useful work. Suck a lock is termed as spin lock.
