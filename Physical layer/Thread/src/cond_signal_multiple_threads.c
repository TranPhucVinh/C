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

// pthread_mutex_t mutex;
pthread_cond_t thread_2_run_condition, thread_3_run_condition;

int main() {  
    // pthread_mutex_init(&mutex, MUTEX_ATTR);
	pthread_t thread_1, thread_2, thread_3;

	pthread_create(&thread_1, NULL, func_thread_1, NULL);
    pthread_create(&thread_2, NULL, func_thread_2, NULL);
    pthread_create(&thread_3, NULL, func_thread_3, NULL);

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
}

void *func_thread_1(void *ptr){    
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 1: %d\n", i);
    }
    thread_2_run = true;
    pthread_cond_signal(&thread_2_run_condition);
    sleep(1);
}

void *func_thread_2(void *ptr){
    while(!thread_2_run){
        printf("Thread 2 isn't ready to run\n");
        sleep(1);   
    }
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 2: %d\n", i);
    }
    thread_3_run = true;
    pthread_cond_signal(&thread_3_run_condition);
}

void *func_thread_3(void *ptr) {
    while(!thread_3_run){
        printf("Thread 3 isn't ready to run\n");
        sleep(1);   
    }

    for (int i = 0; i < RANGE; i++) {
        printf("Thead 3: %d\n", i);
    }
    sleep(1);
}
