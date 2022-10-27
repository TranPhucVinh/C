## One thread function handler to increase a share value issue

Solve the [one thread function handler to increase a share value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Race%20condition.md#one-thread-function-handler-to-increase-a-share-value) with mutex, even with multiple threads, not just 2 tasks:

```c
#include <stdio.h>
#include <pthread.h>

#define RANGE 10000

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
    printf("share_value after executing 2 threads: %d\n", share_value);//30000
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

### Using pthread_mutex_trylock

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

## Examples

### Example 1

**Using a simple boolean variable as a mutex key to implement with 2 tasks**: Finish executing task 1 to print out ``Hello, World !`` 20 times with 1 second delay then execute task 2 to print out count up number from 1 to 20 with 1 second delay.

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

int mutex = 0;

int main()
{  
	pthread_t thread_1, thread_2;
	int thread1_return, thread2_return;

	thread1_return = pthread_create(&thread_1, NULL, func_thread_1, NULL);
    thread2_return = pthread_create(&thread_2, NULL, func_thread_2, NULL);

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
    int number = 0;//Must init variable for proper increment inside while()
    while (mutex) ;
    while(number < 20){
        printf("Hello, World !\n");
        number += 1;
        sleep(1);
    }
    mutex = 1;
}

void *func_thread_2(void *ptr){
    int number = 0;//Must init variable for proper increment inside while()
    while (!mutex) ;
    while(number < 20){
        printf("number: %d\n", number);
        number += 1;
        sleep(1);
    }
    mutex = 0;
}
```

### Example 2

Using mutex to lock the variable

```c
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);
void delaySeconds(long seconds);

pthread_mutex_t lock;

int main()
{  
	pthread_t thread_1, thread_2;
	int thread1_return, thread2_return;

	thread1_return = pthread_create(&thread_1, NULL, func_thread_1, NULL);
    thread2_return = pthread_create(&thread_2, NULL, func_thread_2, NULL);

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
    int number = 0;//Must init variable for proper increment inside while()
    pthread_mutex_lock(&lock);
    while(number < 20){
        printf("Hello, World !\n");
        number += 5;
        delaySeconds(1);
    }
    pthread_mutex_unlock(&lock);
}

void *func_thread_2(void *ptr){
    int number = 0;//Must init variable for proper increment inside while()
    pthread_mutex_lock(&lock);
    while(number < 20){
        printf("number: %d\n", number);
        number += 5;
        delaySeconds(1);
    }
   pthread_mutex_unlock(&lock);
}
```
