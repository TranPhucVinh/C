## Data race issue

Solve the [data race issue stated in fundamental concepts]():

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

(Value of ``displayed_string`` has been updated and is empty)

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