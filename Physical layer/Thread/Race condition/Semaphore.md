# Fundamental concepts

Semaphore is a technique to manage concurrent threads by using an integer value, which is known as a semaphore. The semaphore number is shared between thread to achieve synchronization in the multithread environment.

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

A [mutex](Mutex.md) can be released by the same thread which acquired it while semaphore (especially binary semaphore when compared to mutex) values can be changed by other thread also.

# API

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

# One thread function handler to increase a share value issue, solved by semaphore

Solve the [one thread function handler to increase a share value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Race%20condition.md#one-thread-function-handler-to-increase-a-share-value):

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define PSHARED 0
#define SEM_VAL	1

#define RANGE 10000

int share_value;

void *thread_function(void *ptr);

sem_t mutex;

int main()
{  
    sem_init(&mutex, PSHARED, SEM_VAL);

	pthread_t thread_1, thread_2, thread_3;
	int thread_1_return, thread_2_return, thread_3_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_function, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_function, "Thread 2");
    thread_3_return = pthread_create(&thread_3, NULL, thread_function, "Thread 3");
	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
    printf("share_value after executing 2 threads: %d\n", share_value);//30000
}

void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if (!sem_wait(&mutex)){
			share_value++;
			sem_post(&mutex);
		} else printf("%s fails to lock\n", (char*)ptr);
   }   
}
```

# Accessing a shared variable between 2 thread function handlers issue, solved by semaphore

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define PSHARED 0
#define SEM_VAL	1

sem_t mutex;
char displayed_string[30];

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

char thread_1_str[] = "Thread 1\n";
char thread_2_str[] = "Thread 2\n";

int main()
{
	sem_init(&mutex, PSHARED, SEM_VAL);
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_2, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	sem_destroy(&mutex);
}

void *func_thread_1(void *ptr){
	write(STDOUT_FILENO, thread_1_str, sizeof(thread_1_str));

	if (!sem_wait(&mutex)){
		memcpy(displayed_string, "Hello, World !\n", 15);
		sem_post(&mutex);
	}
}

void *func_thread_2(void *ptr){
	if (!sem_wait(&mutex)){
		write(STDOUT_FILENO, displayed_string, sizeof(displayed_string));
		sem_post(&mutex);
	}
	write(STDOUT_FILENO, thread_2_str, sizeof(thread_1_str));
}
```

**Result**

Run 1st time

```

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

Thread 2
```

That problem happens as in some case thread 2 runs faster than thread 1.
