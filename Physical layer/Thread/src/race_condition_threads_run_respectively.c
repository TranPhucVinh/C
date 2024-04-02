#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE 10

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

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
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 1: %d\n", i);
        sleep(1); // Must have delay so that race condition happens as thread 2 will run while thread 1 hasn't finished running
    }
}

void *func_thread_2(void *ptr){
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 2: %d\n", i);
        sleep(1); // Must have delay so that race condition happens as thread 2 will run while thread 1 hasn't finished running
    }
}
