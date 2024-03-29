# Fundamental concepts

Semaphore is a technique to manage concurrent threads or process by using an integer value, which is known as a semaphore. The semaphore number is shared between thread or process to achieve synchronization in the multithread environment.

The semaphore number can be accessed only through two standard atomic operations ``wait()`` and ``signal()``.

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
This POSIX named semaphore will then be available inside ``/dev/shm/sem.SEMAPHORE_SHARED_MEM``
## sem_init()

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```

``sem_init()`` initializes the unnamed semaphore at the address pointed to by ``sem``. The ``value`` argument specifies the initial value for the semaphore.

The ``pshared`` argument indicates whether this semaphore is to be shared between the threads of a process, or between processes.

If ``pshared`` has the value ``0``, then the semaphore is shared between the threads of a process, and should be located at some address that is visible to all threads (e.g., a global variable, or a variable allocated dynamically on the heap).

If ``pshared`` is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory. For implementation of sem_init with ``pshared`` is nonzero to share between processes to handle race condition, check [Process race condition: Two processes increase the value of a POSIX shared memory region](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Race%20condition#two-processes-increase-the-value-of-a-posix-shared-memory-region) and the [sem_init() implementation to solve that race condition](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Race%20condition/2_processes_increase_a_posix_shared_mem_value_sem_init.c).

## sem_wait() and sem_post()

* **sem_wait()**: decrement/lock the semaphore. If the semaphore's value is >0, then the decrement proceeds, and the function returns immediately. If semaphore's value == 0, then ``sem_wait()`` blocks until either it becomes possible to perform the decrement or or a signal handler interrupts it. **Return**: 0 when success, -1 when fails.
* ``sem_post()``: unlock a semphore

# One thread function handler to increase a shared value issue, solved by binary semaphore

Solve the [one thread function handler to increase a share value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Race%20condition.md#one-thread-function-handler-to-increase-a-share-value): [semaphore_multiple_threads_increase_shared_value.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/semaphore_multiple_threads_increase_shared_value.c)

# Accessing a shared variable between 2 thread function handlers issue, solved by binary semaphore

Program: [semaphore_multiple_threads_access_shared_value.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/semaphore_multiple_threads_access_shared_value.c)

**Result**

| Run 1st time | Run 2nd time | Run 3rd time|
| ------- |:------:|:------:|
| (Empty)<br>Thread 2 <br>Thread 1  <br>| Thread 1<br>Hello, World !<br>Thread 2|Thread 1<br>(Empty)<br>Thread 2|

That problem happens as in some case thread 2 runs faster than thread 1.
# Counting semaphore

Limit the number of threads created by using counting semaphore: Every created thread will take a key. If there are 4 keys but want to create 5 threads, then only 4 threads are created:
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_THREADS     5
#define SEM_VAL         4
#define NO_PROC_SHARED  0 // Not share in processess

sem_t semaphore;

void *thread_function(void *arg) {
    printf("Thread %d is running\n", *((int *)arg));
}

int main() {
    pthread_t threads[NUM_THREADS];

    sem_init(&semaphore, NO_PROC_SHARED, SEM_VAL);

    int _thread_index = 0;

    int sem_val = 0;

    while (!sem_wait(&semaphore)){
        int *arg = (int*)malloc(sizeof(int));
        *arg = _thread_index;
        pthread_create(&threads[_thread_index], NULL, thread_function, arg);
        _thread_index += 1;
    }

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}
```
**Result**
```
Thread 0 is running
Thread 2 is running
Thread 1 is running
Thread 3 is running
// Program blocks permanently after taking all 4 keys
```
