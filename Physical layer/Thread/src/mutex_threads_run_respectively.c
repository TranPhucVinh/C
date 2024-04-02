#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE       5
#define MUTEX_ATTR  NULL // Mutex attribute

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_mutex_t mutex;

int main()
{  
    pthread_mutex_init(&mutex, MUTEX_ATTR);
	pthread_t thread_1, thread_2;
	int thread1_return, thread2_return;

	thread1_return = pthread_create(&thread_1, NULL, func_thread_1, NULL);
    thread2_return = pthread_create(&thread_2, NULL, func_thread_2, NULL);

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 1: %d\n", i);
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
}

void *func_thread_2(void *ptr){
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 2: %d\n", i);
        sleep(1);
    }
   pthread_mutex_unlock(&mutex);
}
