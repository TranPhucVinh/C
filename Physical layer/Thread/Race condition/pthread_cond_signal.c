#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE 3000000

int share_value;

void *thread_func_1(void *ptr);
void *thread_func_2(void *ptr);
int thread_2_run = 0;

pthread_mutex_t lock;
pthread_cond_t thread_2_run_condition;
int main()
{  
	pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&thread_2_run_condition, NULL);
	pthread_t thread_1, thread_2;
	int thread_1_return, thread_2_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_func_1, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_func_2, "Thread 2");
	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    printf("share_value after executing 2 threads: %d\n", share_value);//30000
	pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&thread_2_run_condition);
}

void *thread_func_1(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
			share_value++;
			pthread_mutex_unlock(&lock);
		} else printf("%s fails to lock\n", (char*)ptr);
    }   
    thread_2_run = 1;
    pthread_cond_signal(&thread_2_run_condition);
}

void *thread_func_2(void *ptr){
    for (int i = 0; i < RANGE; i++) {
        if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
        while(!thread_2_run){
            printf("Not ready to run\n");
            pthread_cond_wait(&thread_2_run_condition, &lock);
            // sleep(1);
        }
        share_value++;
        pthread_mutex_unlock(&lock);
        } else printf("%s fails to lock\n", (char*)ptr);
    }
}
