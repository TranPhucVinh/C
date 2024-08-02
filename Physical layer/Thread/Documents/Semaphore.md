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

# POSIX API

* [sem_open()](): create a named semaphore
* [sem_init()](): initializes and unnamed semaphore
* sem_wait() and sem_post()
* sem_getvalue(): get semaphore value

# One thread function handler to increase a shared value issue, solved by binary semaphore

Solve the [one thread function handler to increase a share value issue](Race%20condition.md#one-thread-function-handler-to-increase-a-share-value): [semaphore_multiple_threads_increase_shared_value.c](../src/semaphore_multiple_threads_increase_shared_value.c)

# Accessing a shared variable between 2 thread function handlers issue, solved by binary semaphore

Program: [semaphore_multiple_threads_access_shared_value.c](../src/semaphore_multiple_threads_access_shared_value.c)

**Result**

| Run 1st time | Run 2nd time | Run 3rd time|
| ------- |:------:|:------:|
| (Empty)<br>Thread 2 <br>Thread 1  <br>| Thread 1<br>Hello, World !<br>Thread 2|Thread 1<br>(Empty)<br>Thread 2|

That problem happens as in some case thread 2 runs faster than thread 1.
# Different between binary semaphore and mutex
* A thread can't unlock a mutex for another thread. In mutex, the only way for a thread to unlock a mutex for another thread is to use [condition variable](). Take this example: [suspend_and_resume_threads_by_mutex_and_cond.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/suspend_and_resume_threads_by_mutex_and_cond.c). A [mutex](Mutex.md) can be **released by the same thread which acquired it** while **semaphore** (especially **binary semaphore** when compared to mutex) values can be changed by other thread also, take this example: [suspend_and_resume_threads_by_semaphore.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/suspend_and_resume_threads_by_semaphore.c)
* Binary semaphore is used for multi-process, e.g in case of shared memory, while mutex can only be used inside a single process.
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
**Application**: [Use counting semaphore to limit total number of connected TCP senders in TCP sender - receiver communication](https://github.com/TranPhucVinh/Cplusplus/tree/master/Transport%20layer#single-tcp-receiver-for-multiple-tcp-senders-use-counting-semaphore-to-limit-total-number-of-connected-tcp-senders)
