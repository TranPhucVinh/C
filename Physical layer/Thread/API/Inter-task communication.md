# pthread_mutex_lock()

``pthread_mutex_lock()`` will wait until the mutex is successfully locked so that it will block the program at this waiting time. 
```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```
**Return**: ``0`` when success or ``error_number`` to indicate the error.

Check [One thread function handler to increase a share value issue for its implementation](Mutex.md#use-pthread_mutex_lock).

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
