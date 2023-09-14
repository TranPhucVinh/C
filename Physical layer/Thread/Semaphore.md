# Fundamental concepts

Semaphore is a technique to manage concurrent threads or process by using an integer value, which is known as a semaphore. The semaphore number is shared between thread or process to achieve synchronization in the multithread environment.

The semaphore number can be accessed only through â standard atomic operations ``wait()`` and ``signal()``.

For ``wait()``,  it is used **to test**:

```c
wait() (semphamore_variable S){
	while (S)
	; //No operation
	S--;
}
```

For ``signal()``, it is used **to increment**:

```c
signal(semphamore_variable S){
	S++;
}
```

Types of semaphore:

1. **Binary semaphore**: Semaphore with value can range only ``0`` and ``1``. In some systems, binary semaphores are known as mutex locks, as they are locks that provide mutual exclusions.
2. **Counting semaphore**: Semaphore with value can range over an unrestricted domain. Counting semaphores that are used to manage resources are created so that their initial count value equals the number of resources that are available. To obtain control of a resource, a task must first obtain a semaphore—decrementing the semaphore’s count value. When the count value reaches zero, there are no free resources. When a task finishes with the resource, it ‘gives’ the semaphore back incrementing the semaphore’s count value. 

A [mutex](../Mutex.md) can be released by the same thread which acquired it while semaphore (especially binary semaphore when compared to mutex) values can be changed by other thread also.

# POSIX API
## sem_open()
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
This POSIX named semaphore then be available inside ``/dev/shm/sem.SEMAPHORE_SHARED_MEM``
## sem_init()

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```

``sem_init()`` initializes the unnamed semaphore at the address pointed to by ``sem``. The ``value`` argument specifies the initial value for the semaphore.

The ``pshared`` argument indicates whether this semaphore is to be shared between the threads of a process, or between processes.

If ``pshared`` has the value ``0``, then the semaphore is shared between the threads of a process, and should be located at some address that is visible to all threads (e.g., a global variable, or a variable allocated dynamically on the heap).

If ``pshared`` is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory.

## sem_wait() and sem_post()

* ``sem_wait()``: lock a semaphore
* ``sem_post()``: unlock a semphore

# One thread function handler to increase a shared value issue, solved by semaphore

Solve the [one thread function handler to increase a share value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Race%20condition.md#one-thread-function-handler-to-increase-a-share-value):

Program: [multiple_threads_increase_shared_value.c](src/multiple_threads_increase_shared_value.c)

# Accessing a shared variable between 2 thread function handlers issue, solved by semaphore

Program: [multiple_threads_access_shared_value.c](src/multiple_threads_access_shared_value.c)

**Result**

Run 1st time

```
(Empty)
Thread 2
Thread 1
```

Run 2nd time

```
Thread 1
Hello, World !
Thread 2
```

Run 3rd time:

```
Thread 1
(Empty)
Thread 2
```

That problem happens as in some case thread 2 runs faster than thread 1.
