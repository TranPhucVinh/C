# One thread function handler to increase a share value issue
Solve the [one thread function handler to increase a share value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Race%20condition.md#one-thread-function-handler-to-increase-a-share-value) with mutex, even with multiple threads, not just 2 tasks:
## Use pthread_mutex_lock()
```c
#include <stdio.h>
#include <pthread.h>

#define RANGE 3000000

int share_value;

void *thread_function(void *ptr);

pthread_mutex_t lock;

int main()
{  
	pthread_mutex_init(&lock, NULL);
	pthread_t thread_1, thread_2, thread_3;
	int thread_1_return, thread_2_return, thread_3_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_function, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_function, "Thread 2");
    thread_3_return = pthread_create(&thread_3, NULL, thread_function, "Thread 3");
	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
    printf("share_value after executing 2 threads: %d\n", share_value);//9000000
	pthread_mutex_destroy(&lock);
}

void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
			share_value++;
			pthread_mutex_unlock(&lock);
		} else printf("%s fails to lock\n", (char*)ptr);
   }   
}
```
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