# Thead definition

In computer science, a thread of execution is **the smallest sequence of programmed instructions** that can be managed independently by a scheduler, which is typically a part of the operating system and can be thought as a unit of execution within a process.

The implementation of threads and processes differs between systems, like in MCU and OS, but in most cases a thread is a component of a process. Multiple threads can exist within one process, executing concurrently and sharing resources such as memory.

A thread has its own:
* Thread ID
* Stack and local variables

Threads implemented in Unix are POSIX threads. ``pthreads`` is C POSIX threads library.

Compile: ``gcc test.c -lpthread``
# Create a thread to print out a string

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
## pthread_create()

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

The ``pthread_create()`` function starts a new thread in the calling process. The new thread starts execution by invoking ``start_routine()``; ``arg`` is passed as the sole argument of ``start_routine()``. It means, simply calling ``pthread_create()`` will start executing the thread.

The ``attr`` argument points to a ``pthread_attr_t`` structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using ``pthread_attr_init()`` and related functions. If ``attr`` is ``NULL``, then the thread is created with default attributes.

Before returning, a successful call to ``pthread_create()`` stores the ID of the new thread in the buffer pointed to by ``thread``, known as **thread ID**; this identifier is used to refer to the thread in subsequent calls to other pthreads functions.

On success, **pthread_create()** returns **0**; on error, it returns an ``error number``, and the contents of ``*thread`` are ``undefined``.
## Program's flow

* **Step 1**: Execute thread 1. [pthread_join()](../API/Thread%20creation.md#pthread_join) will make the current process to wait for all operations in thread 1 to finish.
* **Step 2**: Perform program operation after thread 1 finishes executing, i.e perform program operation behind [pthread_join()](../API/Thread%20creation.md#pthread_join)

If the thread is an infinite loop, the program operation behind [pthread_join()](../API/Thread%20creation.md#pthread_join) can't be reached.

When not using [pthread_join()](../API/Thread%20creation.md#pthread_join):

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
# pthread_self() and thread ID

```c
pthread_t pthread_self(void);
```

The ``pthread_self()`` function **returns the ID of the calling thread**. This is the same value that is returned in ``*thread`` in the **pthread_create()** call that created this thread.

That ID is the special ID used by the POSIX Thread API, which is not equal to the thread ID returned by **syscall(SYS_gettid)**.

**syscall(SYS_gettid)** returns the thread ID managed by the system, not by the POSIX Thread API. In a single-threaded process, **syscall(SYS_gettid)** value is equal to the process ID returned by **getpid()** as **main()** is a thread, i.e the main thread of the process.  In a multithreaded process, the **syscall(SYS_gettid)** value in each thread are unique.
```c
#include <sys/syscall.h> 

pthread_barrier_t barrier;

void *thread_func(void *ptr){
    printf("thread ID: %ld\n", syscall(SYS_gettid));
    while(1){
        printf("Hello, World !\n");
        sleep(1);
    }
}

int main()
{  
    printf("PID: %d\n", getpid());
    printf("Main thread ID: %ld\n", syscall(SYS_gettid));// Equal to getpid()
	pthread_t thread_id;

    pthread_create(&thread_id, NULL, thread_func, NULL);
    pthread_join(thread_id, NULL);
}
```
**Result**
```
PID: 1614500
Main thread ID: 1614500
thread ID: 1614501
Hello, World !
Hello, World !
...
```
To **view all threads created by a process**, Go to ``/proc/<pid>``, e.g ``/proc/1614500`` in this case. ``ls /proc/1614500/task`` returns ``1614500`` and ``1614501``
