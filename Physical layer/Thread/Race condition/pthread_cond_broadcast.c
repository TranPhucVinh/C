#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE 3000000

int share_value;

void *thread_func_1(void *ptr);
void *thread_func_2(void *ptr);
void *thread_func_3(void *ptr);

int multithread_run = 0;

pthread_mutex_t lock;
pthread_cond_t multithread_cond;

int main()
{  
	pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&multithread_cond, NULL);

	pthread_t thread_1, thread_2, thread_3;
	int thread_1_return, thread_2_return, thread_3_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_func_1, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_func_2, "Thread 2");
    thread_3_return = pthread_create(&thread_3, NULL, thread_func_3, "Thread 3");

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
    printf("share_value after executing 3 threads: %d\n", share_value);//
	pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&multithread_cond);
}

void *thread_func_1(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
			share_value++;
			pthread_mutex_unlock(&lock);
		} else printf("%s fails to lock\n", (char*)ptr);
    }   
    multithread_run = 1;
    pthread_cond_broadcast(&multithread_cond);
}

void *thread_func_2(void *ptr){
    for (int i = 0; i < RANGE; i++) {
        if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
        while(!multithread_run){
            printf("Not ready to run\n");
            pthread_cond_wait(&multithread_cond, &lock);
        }
        share_value++;
        pthread_mutex_unlock(&lock);
        } else printf("%s fails to lock\n", (char*)ptr);
    }
}

void *thread_func_3(void *ptr){
    for (int i = 0; i < RANGE; i++) {
        if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
        while(!multithread_run){
            printf("Not ready to run\n");
            pthread_cond_wait(&multithread_cond, &lock);
        }
        share_value++;
        pthread_mutex_unlock(&lock);
        } else printf("%s fails to lock\n", (char*)ptr);
    }
}
