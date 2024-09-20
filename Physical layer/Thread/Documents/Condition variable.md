Mutex provides mutual exclusion for accessing the shared variable, while the condition variable is used to signal changes in the variable’s state. Pthread condition variable is used in multithread which have already involved mutex.

# One thread unblocks another thread
In this example, after increasing the ``shared_value`` to its ``RANGE``, thread 1 will set flag ``thread_2_run`` to allow thread 2 to run. After being "enabled" by flag ``thread_2_run``, thread 2 will increase the ``shared_value`` to ``RANGE``. This example is quite similar to [One thread function handler to increase a shared value issue](#one-thread-function-handler-to-increase-a-shared-value), except ``thread_1`` uses flag ``thread_2_run`` to enable ``thread_2`` to run.

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE 3000000

int shared_value;

void *thread_func_1(void *ptr);
void *thread_func_2(void *ptr);
int thread_2_run = 0;

pthread_mutex_t lock;

int main()
{  
	pthread_mutex_init(&lock, NULL);
	pthread_t thread_1, thread_2;
	int thread_1_return, thread_2_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_func_1, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_func_2, "Thread 2");
	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    printf("shared_value after executing 2 threads: %d\n", shared_value);
	pthread_mutex_destroy(&lock);
}

void *thread_func_1(void *ptr){
    printf("Thread 1 starts\n");
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){
			shared_value++;
			pthread_mutex_unlock(&lock);
		} else printf("%s fails to lock\n", (char*)ptr);
    }   
    thread_2_run = 1;
    printf("shared_value after thread 1: %d\n", shared_value);
}

void *thread_func_2(void *ptr){
    printf("Thread 2 starts\n");
    for (int i = 0; i < RANGE; i++) {
        if(!pthread_mutex_lock(&lock)){
        while(!thread_2_run){
            printf("Thread 2 isn't ready to run\n");
            sleep(1);
        }
        shared_value++;
        pthread_mutex_unlock(&lock);
        } else printf("%s fails to lock\n", (char*)ptr);
    }
    printf("shared_value after thread 2: %d\n", shared_value);
}
```
**Result**
```
Thread 1 starts
Thread 2 starts
Thread 2 isn't ready to run
Thread 2 isn't ready to run
...// Loop forever
```

**Problem solved by pthread condition variable**: [cond_signal_2_threads.c](../src/cond_signal_2_threads.c)

**Result**
```
Thread 1 starts
Thread 2 starts
Not ready to run
shared_value after thread 1: 3000000
shared_value after thread 2: 6000000
shared_value after executing 2 threads: 6000000
```
# One thread unblocks multiple threads
For thread 1 to allow multiple other threads, e.g thread 2, thread 3 to run, we must use [pthread_cond_broadcast()]() to broadcast the condition variable from thread 1.

**Program**: [cond_broadcast.c](../src/cond_broadcast.c)

**Result**
```
Not ready to run
Not ready to run
share_value after executing 3 threads: 9000000
```
# Run multiple threads respectively by condition variables
Run thread 1, 2 and 3 respectively by using condition variables: [cond_signal_multiple_threads.c](../src/cond_signal_multiple_threads.c). Also note that this program implementation doesn't include mutex
