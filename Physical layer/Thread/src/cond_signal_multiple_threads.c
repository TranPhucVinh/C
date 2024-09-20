#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE       5
#define MUTEX_ATTR  NULL // Mutex attribute

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);
void *func_thread_3(void *ptr);

bool thread_2_run = false, thread_3_run = false;

pthread_mutex_t mutex;
pthread_cond_t thread_2_run_condition, thread_3_run_condition;

int main() {  
    pthread_mutex_init(&mutex, MUTEX_ATTR);
	pthread_t thread_1, thread_2, thread_3;
	int thread1_return, thread2_return, thread3_return;

	thread1_return = pthread_create(&thread_1, NULL, func_thread_1, NULL);
    thread2_return = pthread_create(&thread_2, NULL, func_thread_2, NULL);
    thread3_return = pthread_create(&thread_3, NULL, func_thread_3, NULL);

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 1: %d\n", i);
    }
    pthread_mutex_unlock(&mutex);
    thread_2_run = true;
    pthread_cond_signal(&thread_2_run_condition);
    sleep(1);
}

void *func_thread_2(void *ptr){
    pthread_mutex_lock(&mutex);
    while(!thread_2_run){
        printf("Thread 2 isn't ready to run\n");
        sleep(1);   
    }
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 2: %d\n", i);
    }
    pthread_mutex_unlock(&mutex);
    thread_3_run = true;
    pthread_cond_signal(&thread_3_run_condition);
    sleep(1);
}

void *func_thread_3(void *ptr) {
    pthread_mutex_lock(&mutex);
    while(!thread_3_run){
        printf("Thread 3 isn't ready to run\n");
        sleep(1);   
    }

    for (int i = 0; i < RANGE; i++) {
        printf("Thead 3: %d\n", i);
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
}
