### Example 1

Using a simple boolean variable as a mutex key to implement with 2 tasks

```c
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);
void delaySeconds(long seconds);

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
        delaySeconds(1);
    }
    mutex = 1;
}

void *func_thread_2(void *ptr){
    int number = 0;//Must init variable for proper increment inside while()
    while (!mutex) ;
    while(number < 20){
        printf("number: %d\n", number);
        number += 1;
        delaySeconds(1);
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