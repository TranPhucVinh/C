#include <stdio.h>
#include <pthread.h>

#define RANGE 3000000

int share_value;

void *thread_function(void *ptr);

pthread_mutex_t lock;

int main()
{  
	pthread_mutex_init(&lock, NULL);
	pthread_t thread_1, thread_2, thread_3;
	int thread_1_return, thread_2_return, thread_3_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_function, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_function, "Thread 2");
    thread_3_return = pthread_create(&thread_3, NULL, thread_function, "Thread 3");
	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
    printf("share_value after executing 2 threads: %d\n", share_value);//9000000
	pthread_mutex_destroy(&lock);
}

void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){//pthread_mutex_lock() returns 0 if success.
			share_value++;
			pthread_mutex_unlock(&lock);
		} else printf("%s fails to lock\n", (char*)ptr);
   }   
}
