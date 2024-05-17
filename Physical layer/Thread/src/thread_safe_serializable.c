#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define ARR_SZ      5
#define RANGE       100000000
#define MUTEX_ATTR  NULL // Mutex attribute

void *thread_function(void *ptr);

pthread_mutex_t lock;

int array[ARR_SZ];

int main()
{  
    pthread_mutex_init(&lock, MUTEX_ATTR);
	pthread_t thread_1, thread_2;
	int thread1_return, thread2_return;

	thread1_return = pthread_create(&thread_1, NULL, thread_function, NULL);
    thread2_return = pthread_create(&thread_2, NULL, thread_function, NULL);

	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    for (int i = 0; i < ARR_SZ; i++){
       printf("%d ", array[i]);
    }
}

void *thread_function(void *ptr){
    for (int i = 0; i < ARR_SZ; i++){
        if(!pthread_mutex_lock(&lock)){
            for (int j = 0; j < RANGE; j++) {
                array[i]++;
            } 
            pthread_mutex_unlock(&lock);
        } else printf("Mutex fails to lock\n");
    }
    return NULL;
}
