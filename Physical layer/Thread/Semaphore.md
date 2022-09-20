# API

### sem_init()

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```

``sem_init()`` initializes the unnamed semaphore at the address pointed to by ``sem``. The ``value`` argument specifies the initial value for the semaphore.

The ``pshared`` argument indicates whether this semaphore is to be shared between the threads of a process, or between processes.

If ``pshared`` has the value ``0``, then the semaphore is shared between the threads of a process, and should be located at some address that is visible to all threads (e.g., a global variable, or a variable allocated dynamically on the heap).

If ``pshared`` is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory.

### sem_wait() and sem_post()

* ``sem_wait()``: lock a semaphore
* ``sem_post()``: unlock a semphore

## Data race issue

Solve the [data race issue stated in fundamental concepts](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Thread#data-race):

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

## Problem when resource is not controlled

Thread issue:

```c
#include <stdio.h>
#include <pthread.h>

char displayed_string[30];

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

int main()
{
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_2, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
	printf("Thread 1\n");
	sprintf(displayed_string, "%s", "Hello, World !");	
}

void *func_thread_2(void *ptr){
	printf("%s\n", displayed_string);
	printf("Thread 2\n");
}
```

```
Thread 1

Thread 2
```

(Value of ``displayed_string`` hasn't been updated so it is empty. **This is the result from race condition**).

If change to:

```c
void *func_thread_2(void *ptr){	
	printf("Thread 2\n");
	printf("%s\n", displayed_string);
}
```

```
Thread 1
Thread 2
Hello, World !
```

Beside race condition, that issue also happens due to using ``printf()`` and ``sprintf()``. Use ``write()`` and ``memcpy()`` will minimize the race condition incidents (as the result from race condition still happen but very little)

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

char displayed_string[30];

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

char thread_1_str[] = "Thread 1\n";
char thread_2_str[] = "Thread 2\n";

int main()
{
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_2, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
	write(STDOUT_FILENO, thread_1_str, sizeof(thread_1_str));
	memcpy(displayed_string, "Hello, World !\n", 15);
}

void *func_thread_2(void *ptr){
	write(STDOUT_FILENO, displayed_string, sizeof(displayed_string));
	write(STDOUT_FILENO, thread_2_str, sizeof(thread_1_str));
}
```

### Problem when using semaphore

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define PSHARED 0
#define SEM_VAL	1

char displayed_string[30];
sem_t mutex;

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

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
	printf("Thread 1\n");

	if (!sem_wait(&mutex)){
        sprintf(displayed_string, "%s", "Hello, World !");	
        sem_post(&mutex);
    } else printf("Thread 1 fails to lock\n");

    pthread_exit(0);
}

void *func_thread_2(void *ptr){
    if (!sem_wait(&mutex)){
        printf("%s\n", displayed_string);
        sem_post(&mutex);
    } else printf("Thread 2 fails to lock\n");
	printf("Thread 2\n");

    pthread_exit(0);
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

That problem happens as in some case thread 2 runs faster than thread 1

If using ``sleep(1)`` inside infinite threads, the issue still happens:

```c
void *func_thread_1(void *ptr){
	printf("Thread 1\n");
    int number = 0;

    while (1){
        if (!sem_wait(&mutex)){
            sprintf(displayed_string, "%s %d", "Hello, World !; index: ", number);	
            sem_post(&mutex);
        } else printf("Thread 1 fails to lock\n");
        number += 1;

        sleep(1);
    }

    pthread_exit(0);
}

void *func_thread_2(void *ptr){

    while (1){
        if (!sem_wait(&mutex)){
            printf("%s\n", displayed_string);
            sem_post(&mutex);
        } else printf("Thread 2 fails to lock\n");

        sleep(1);
    }

    printf("Thread 2\n");
    pthread_exit(0);
}
```

Run 1st time:

```
Thread 1

Hello, World !; index:  0
Hello, World !; index:  1
Hello, World !; index:  2
...
```

Run 2nd time:

```
Thread 1

Hello, World !; index:  1
Hello, World !; index:  2
Hello, World !; index:  3
...
```

Run 3rd time:

```
Thread 1

Hello, World !; index:  1
Hello, World !; index:  2
Hello, World !; index:  2
Hello, World !; index:  3
Hello, World !; index:  5
Hello, World !; index:  5
...
```
