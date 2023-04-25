# One thread function handler to increase a share value issue
Solve the [one thread function handler to increase a share value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Race%20condition.md#one-thread-function-handler-to-increase-a-share-value) with mutex, even with multiple threads, not just 2 tasks:
## Use pthread_mutex_lock()

**Program**: [pthread_mutex_lock.c](pthread_mutex_lock.c)

**Result**: ``share_value after executing 2 threads: 9000000``
## Using pthread_mutex_trylock()

With ``pthread_mutex_trylock()``, if fails to lock the mutex, the thread will handle other task

```c
/*
    int main() and other operations are like 
    pthread_mutex_lock() example
*/
void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
      	if (!pthread_mutex_trylock(&lock)){
			share_value++;
			pthread_mutex_unlock(&lock);
		} else {
			printf("Didn't get lock in %s, %d\n", (char*)ptr, lock_count);
			lock_count += 1;
		}
   }   
}
```
**Result**

```
Didn't get lock in Thread 2, 0
Didn't get lock in Thread 1, 1
Didn't get lock in Thread 2, 2
Didn't get lock in Thread 2, 3
...

Didn't get lock in Thread 3, 244
Didn't get lock in Thread 2, 245
Didn't get lock in Thread 1, 117
share_value after executing 2 threads: 29753
```

# Using a simple boolean variable as a mutex key to implement with 2 tasks

Finish executing task 1 to print out ``Hello, World !`` 20 times with 1 second delay then execute task 2 to print out count up number from 1 to 20 with 1 second delay.

Program: [simple_boolean_variable_as_mutex.c](simple_boolean_variable_as_mutex.c)

# Using mutex to lock the variable

Instead of using a boolean variable [like above](#using-a-simple-boolean-variable-as-a-mutex-key-to-implement-with-2-tasks), mutex can be used as the lock between 2 threads: [mutex_to_lock_the_variables.c](mutex_to_lock_the_variables.c)

# Condition variable
pthread condition variable is used in multithread which have already involved mutex
## One thread unblocks another thread
In this example, after increasing the ``share_value`` to its ``RANGE``, thread 1 will set ``thread_2_run`` to allow thread 2 to run. Thread 2 will wait for ``thread_2_run`` then increases the ``share_value`` to ``RANGE``. This example is quite similar to [One thread function handler to increase a share value issue
](), except it has the flag ``thread_2_run`` to block thread 2 from running.

```cpp
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE 3000000

int share_value;

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
    printf("share_value after executing 2 threads: %d\n", share_value);
	pthread_mutex_destroy(&lock);
}

void *thread_func_1(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){
			share_value++;
			pthread_mutex_unlock(&lock);
		} else printf("%s fails to lock\n", (char*)ptr);
    }   
    thread_2_run = 1;
}

void *thread_func_2(void *ptr){
    for (int i = 0; i < RANGE; i++) {
        if(!pthread_mutex_lock(&lock)){
        while(!thread_2_run){
            printf("Not ready to run\n");
            sleep(1);
        }
        share_value++;
        pthread_mutex_unlock(&lock);
        } else printf("%s fails to lock\n", (char*)ptr);
    }
}
```
```
Not ready to run
Not ready to run
...//Loop forever
```
**Note**: One way to solve that issue is to use a [simple boolean variable as mutex](simple_boolean_variable_as_mutex.c).

**Problem solved by pthread conditional variable**: [pthread_cond_signal.c](pthread_cond_signal.c)

## One thread unblocks multiple threads
For thread 1 to allow multiple other threads, e.g thread 2, thread 3 to run, we must use [pthread_cond_broadcast()]() to broadcast the condition variable from thread 1.

**Program**: [pthread_cond_broadcast.c](pthread_cond_broadcast.c)

**Result**
```
Not ready to run
Not ready to run
share_value after executing 3 threads: 9000000
```
