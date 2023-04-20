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

If ``retval`` is not ``NULL``, then ``pthread_join()`` copies the exit status  of the target thread (i.e., the value that the target thread supplied to ``pthread_exit()``) into the location pointed to by ``retval``.  If the target thread was canceled, then ``PTHREAD_CANCELED`` is placed in the location pointed to by ``retval``.

On success, ``pthread_join()`` returns ``0``; on error, it returns an error number.

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
