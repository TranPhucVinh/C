#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define RANGE 5

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
    while (mutex);
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 1: %d\n", i);
        sleep(1);
    }
    mutex = 1;
}

void *func_thread_2(void *ptr){
    while (!mutex);
    for (int i = 0; i < RANGE; i++) {
        printf("Thead 2: %d\n", i);
        sleep(1);
    }
    mutex = 0;
}
