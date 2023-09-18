# pthread_create()

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

The ``pthread_create()`` function starts a new thread in the calling process. The new thread starts execution by invoking ``start_routine()``; ``arg`` is passed as the sole argument of ``start_routine()``. It means, simply call ``pthread_create()`` will start executing the thread.

The ``attr`` argument points to a ``pthread_attr_t`` structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using ``pthread_attr_init()`` and related functions. If ``attr`` is ``NULL``, then the thread is created with default attributes.

Before returning, a successful call to ``pthread_create()`` stores the ID of the new thread in the buffer pointed to by ``thread``, known as **thread ID**; this identifier is used to refer to the thread in subsequent calls to other pthreads functions.

On success, ``pthread_create()`` returns ``0``; on error, it returns an ``error number``, and the contents of ``*thread`` are ``undefined``.

# pthread_join()

```c
int pthread_join(pthread_t thread, void **retval);
```

The ``pthread_join()`` function waits for the thread specified by ``thread`` to terminate. If that thread has already terminated, then ``pthread_join()`` returns immediately. The thread specified by ``thread`` must be joinable.

If ``retval`` is not ``NULL``, then ``pthread_join()`` copies the exit status  of the target thread (i.e., the value that the target thread supplied to [pthread_exit()](API.md#pthread_exit)) into the location pointed to by ``retval``.  If the target thread was canceled, then ``PTHREAD_CANCELED`` is placed in the location pointed to by ``retval``.

On success, ``pthread_join()`` returns ``0``; on error, it returns an error number.

**Important note**: **pthread_join() doesn't start, create or join the specified thread to the current process** as **pthread_create()** has already done that. **pthread_join()** just simply waits for the thread it specified to finish execution. [Using pthread_join() for the thread included while(1) loop will block the program](#).
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
}
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
# pthread_self()

```c
pthread_t pthread_self(void);
```

The ``pthread_self()`` function **returns the ID of the calling thread**. This is the same value that is returned in *thread in the ``pthread_create()`` call that created this thread.

**Note**: This function must always be called inside the thread function handler so that it can get the proper thread ID of the calling thread. Check [pthread implementation to create a thread to print out a string](README.md#create-a-thread-to-print-out-a-string)

# pthread_mutex_lock()

``pthread_mutex_lock()`` will wait until the mutex is successfully locked so that it will block the program at this waiting time. Check [One thread function handler to increase a share value issue for its implementation](Mutex.md#use-pthread_mutex_lock).

# pthread_mutex_trylock()

``pthread_mutex_trylock()`` will check if the mutex is available for locking and return immediately without waiting. Check [One thread function handler to increase a share value issue for its implementation](Mutex.md#using-pthread_mutex_trylock).
# pthread_cond_init()
```c
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
```
The function ``pthread_cond_init()`` initialises the condition variable referenced by ``cond`` with attributes referenced by ``attr``. If ``attr`` is ``NULL``, the default condition variable attributes are used.
# pthread_cond_wait()
```c
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
```
``pthread_cond_wait()`` will block on a condition variable. They are called with ``mutex`` locked by the calling thread.

These functions atomically release ``mutex`` and cause the calling thread to block on the condition variable ``cond``; atomically here means "atomically with respect to access by another thread to the mutex and then the condition variable". That is, if another thread is able to acquire the mutex after the about-to-block thread has released it, then a subsequent call to [pthread_cond_signal() or pthread_cond_broadcast()](##pthread_cond_signal-and-pthread_cond_broadcast) in that thread behaves as if it were issued after the about-to-block thread has blocked.

# pthread_cond_signal() and pthread_cond_broadcast()
```c
int pthread_cond_signal(pthread_cond_t *cond);
```
```c
int pthread_cond_broadcast(pthread_cond_t *cond);
```

These two functions are used to unblock threads blocked on a condition variable.

The ``pthread_cond_signal()`` call unblocks at least one of the threads that are blocked on the specified condition variable ``cond`` (if any threads are blocked on ``cond``).

The ``pthread_cond_broadcast()`` call unblocks all threads currently blocked on the specified condition variable ``cond``.

# pthread_cond_destroy()
```c
int pthread_cond_destroy(pthread_cond_t *cond);
```
