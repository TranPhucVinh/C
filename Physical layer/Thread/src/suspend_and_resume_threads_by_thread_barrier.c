#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define THREAD_BARRIERS_NUMBER  2
#define PTHREAD_BARRIER_ATTR    NULL // pthread barrier attribute

void *suspend_thread_func(void *ptr);
void *resume_thread_func(void *ptr);

int number = 0;

pthread_t suspend_thread, resume_thread;
pthread_barrier_t barrier;

void resumeThread()
{ 
    pthread_barrier_wait(&barrier);
}

void suspendThread()
{ 
    pthread_barrier_wait(&barrier);
}

int main(void){
        pthread_barrier_init(&barrier, PTHREAD_BARRIER_ATTR, THREAD_BARRIERS_NUMBER);
    pthread_create(&suspend_thread, NULL, suspend_thread_func, NULL);
    pthread_create(&resume_thread, NULL, resume_thread_func, NULL);

	pthread_join(suspend_thread, NULL);
    pthread_join(resume_thread, NULL);

	return 0;
}

void *suspend_thread_func(void *ptr){
    while (1){
		number += 1;
        printf("number %d\n", number);
		if (number == 3) {
            printf("Task is suspended\n");
            suspendThread();
            printf("Task is resumed\n");
            pthread_barrier_destroy(&barrier);
    	}
		sleep(1);
	}
}

void *resume_thread_func(void *ptr){
    while (1){
		if (number == 3){
            sleep(3);
            resumeThread();
            printf("Hello, world ! Has delay for 3 seconds in resume_thread\n");
        }
        // Wait for 2 seconds which is bigger than 1 second wait in suspend_thread
        // so that number is increased properly
        sleep(2);
    }	
}