# pthread_create()

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

The ``pthread_create()`` function starts a new thread in the calling process. The new thread starts execution by invoking ``start_routine()``; ``arg`` is passed as the sole argument of ``start_routine()``. It means, simply calling ``pthread_create()`` will start executing the thread.

The ``attr`` argument points to a ``pthread_attr_t`` structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using ``pthread_attr_init()`` and related functions. If ``attr`` is ``NULL``, then the thread is created with default attributes.

Before returning, a successful call to ``pthread_create()`` stores the ID of the new thread in the buffer pointed to by ``thread``, known as **thread ID**; this identifier is used to refer to the thread in subsequent calls to other pthreads functions.

On success, **pthread_create()** returns **0**; on error, it returns an ``error number``, and the contents of ``*thread`` are ``undefined``.

# pthread_join()

```c
int pthread_join(pthread_t thread, void **retval);
```

The **pthread_join()** function waits for the thread specified by **thread** to terminate. If that thread has already terminated, then ``pthread_join()`` returns immediately. The thread specified by ``thread`` must be joinable.

**pthread_join() doesn't start, create or join the specified thread to the current process** as **pthread_create()** has already done that. **pthread_join()** just simply waits for the thread it specified to finish execution. [Using pthread_join() for the thread included while(1) loop will block the program](#pthread_join-will-block-the-process-if-the-thread-it-specifies-included-while1).

If **retval** is not ``NULL``, then **pthread_join()** copies the exit status  of the target thread (i.e., the value that the target thread supplied to [pthread_exit()](API.md#pthread_exit)) into the location pointed to by ``retval``.  If the target thread was canceled, then ``PTHREAD_CANCELED`` is placed in the location pointed to by ``retval``.

On success, ``pthread_join()`` returns ``0``; on error, it returns an error number.

## pthread_join() will block the process if the thread it specifies included while(1)

The thread specified by pthread_join() which includes ``while(1)`` like this will block the program. The lines of code befine pthread_join() then won't be reached:
```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *display_string(void *ptr){
	while (1){
        printf("%s\n", (char*)ptr);
        sleep(1);
    }
}

int main()
{  
	pthread_t thread_id;
	pthread_t str_thread;
    char str[] = "Hello, World !";
    pthread_create(&str_thread, NULL, display_string, str);
	pthread_join(str_thread, NULL);
	printf("str_thread_ finish executing\n");//This line of code won't be reached as pthread_join() has blocked the program
    printf("Thread ID %lu\n", thread_id);//This line of code won't be reached as pthread_join() has blocked the program
	while(1){//This while(1) loop won't be reached as pthread_join() has blocked the program
		printf("Thread display_string() is running now\n");
		sleep(1);
	}
}
```
**Result**:
```
Hello, World !
Hello, World !
...
```
To avoid blocking, simply remove **pthread_join()**:
```c
pthread_t thread_id;
pthread_t str_thread;
char str[] = "Hello, World !";
pthread_create(&str_thread, NULL, display_string, str);
// pthread_join(str_thread, NULL);
printf("str_thread finish executing\n");//This line of code won't be reached as pthread_join() has blocked the program
printf("Thread ID %lu\n", thread_id);//This line of code won't be reached as pthread_join() has blocked the program
while(1){//This while(1) loop won't be reached as pthread_join() has blocked the program
	printf("Thread display_string() is running now\n");
	sleep(1);
}
```
**Result**
```
str_thread finish executing
Thread ID 0
Thread display_string() is running now
Hello, World !
...
```
# pthread_detach()
```cpp
int pthread_detach(pthread_t thread);
```
Using [pthread_detach()]() to run the thread independently. This is useful to avoid the thread which includes the infinitely loop blocking the program:
In [the pthread_join() program above which blocks the process as its thread includes while(1)](#pthread_join-will-block-the-process-if-the-thread-it-specifies-included-while1), change pthread_join() to pthread_detach():
```cpp
pthread_t thread_id;
pthread_t str_thread;
char str[] = "Hello, World !";
pthread_create(&str_thread, NULL, display_string, str);
pthread_detach(str_thread);
printf("str_thread_ finish executing\n");
printf("Thread ID %lu\n", thread_id);
while(1){
	printf("Thread display_string() is running now\n");
	sleep(1);
}
```
**Result**
```
str_thread_ finish executing
Thread ID 0
Thread display_string() is running now
Hello, World !
Thread display_string() is running now
Hello, World !
...
```
# pthread_exit()
```c
void pthread_exit(void *retval);
```
Exit the current calling thread and return its ``void *retval`` to ``void **retval`` of ``pthread_join()``.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *func_thread(void *ptr);
int main()
{  
    int **thread_1_return;
	pthread_t thread_1;

    thread_1_return = (int**) malloc(sizeof(int**));
	pthread_create(&thread_1, NULL, func_thread, NULL);
	pthread_join(thread_1, (void**)thread_1_return);
    printf("value: %d\n", **thread_1_return);//567
}

void *func_thread(void *ptr){
    int *number = (int*) malloc (sizeof(int));
    *number = 567;
    printf("Thread is exited/terminated\n");
    pthread_exit(number);
    printf("This line won't be called\n");// This line won't be called as thread is exited
    *number = 123;
	return number;//This return value setup won't be reached as pthread_exit() is called above
}
```
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
To view all threads created by a process. Go to ``/proc/<pid>``, e.g ``/proc/1614500`` in this case. ``ls /proc/1614500/task`` returns ``1614500`` and ``1614501``