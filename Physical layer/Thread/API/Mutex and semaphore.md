# pthread_mutex_lock()

``pthread_mutex_lock()`` will wait until the mutex is successfully locked so that it will block the program at this waiting time. 
```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```
**Return**: ``0`` when success or ``error_number`` to indicate the error.

Check [One thread function handler to increase a share value issue for its implementation](Mutex.md#use-pthread_mutex_lock).

# pthread_mutex_trylock()

``pthread_mutex_trylock()`` will check if the mutex is available for locking and return immediately without waiting. Check [One thread function handler to increase a share value issue for its implementation](../Documents/Mutex.md#using-pthread_mutex_trylock).
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
# sem_open()
``sem_open()`` will create a named semaphore
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define SEM_NAME    "/SEMAPHORE_SHARED_MEM"//Semaphore for shared memory; must started with /
#define SEM_INIT_vALUE  1 //Semaphore initialize value
sem_t *sem;

int main(){
    sem = sem_open(SEM_NAME, O_CREAT|O_RDWR, 777, SEM_INIT_vALUE);
    if (sem == SEM_FAILED) {
        printf("Fail to create %s\n", SEM_NAME);
        printf("errno %d\n", errno);
        if (errno == 13) printf("Permission denied\n");
    }
    else printf("Create %s successfully\n", SEM_NAME);
}
```
This POSIX named semaphore will then be available inside ``/dev/shm/sem.SEMAPHORE_SHARED_MEM``
# sem_init()

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```

``sem_init()`` initializes the unnamed semaphore at the address pointed to by ``sem``. The ``value`` argument specifies the initial value for the semaphore.

The ``pshared`` argument indicates whether this semaphore is to be shared between the threads of a process, or between processes.

If ``pshared`` has the value ``0``, then the semaphore is shared between the threads of a process, and should be located at some address that is visible to all threads (e.g., a global variable, or a variable allocated dynamically on the heap).

If ``pshared`` is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory. For implementation of sem_init with ``pshared`` is nonzero to share between processes to handle race condition, check [Process race condition: Two processes increase the value of a POSIX shared memory region](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Race%20condition#two-processes-increase-the-value-of-a-posix-shared-memory-region) and the [sem_init() implementation to solve that race condition](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Race%20condition/2_processes_increase_a_posix_shared_mem_value_sem_init.c).
# sem_wait() and sem_post()

* **sem_wait()**: decrement/lock the semaphore. If the semaphore's value is >0, then the decrement proceeds, and the function returns immediately. If semaphore's value == 0, then ``sem_wait()`` blocks until either it becomes possible to perform the decrement or or a signal handler interrupts it. **Return**: 0 when success, -1 when fails.
* **sem_post()**: unlock a semphore
# sem_getvalue()
``sem_getvalue()`` is used to get semaphore value
```cpp
int shared_value;
sem_t bin_sem;// Binary semaphore

int main()
{  
    sem_init(&bin_sem, NO_PROC_SHARED, SEM_VAL);

	pthread_t thread_id;
	int thread_return;

	thread_return = pthread_create(&thread_id, NULL, thread_function, "Thread 1");
	pthread_join(thread_id, NULL);
    printf("shared_value: %d\n", shared_value);//1
}

void *thread_function(void *ptr){
    if (!sem_wait(&bin_sem)){
        int sem_val;

        sem_getvalue(&bin_sem, &sem_val);
        printf("Semaphore value after sem_wait(): %d\n", sem_val);

        shared_value++;

        sem_post(&bin_sem);
        sem_getvalue(&bin_sem, &sem_val);
        printf("Semaphore value after sem_post(): %d\n", sem_val);
    } else printf("%s fails to lock\n", (char*)ptr);
}
```
