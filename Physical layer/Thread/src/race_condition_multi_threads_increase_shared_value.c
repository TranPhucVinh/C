#include <stdio.h>
#include <pthread.h>

#define RANGE 10000

int share_value;

void *thread_function(void *ptr);

int main()
{  
	pthread_t thread_1, thread_2;
	int thread_1_return, thread_2_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_function, NULL);
   thread_2_return = pthread_create(&thread_2, NULL, thread_function, NULL);
	pthread_join(thread_1, NULL);
   pthread_join(thread_2, NULL);
   printf("share_value after executing 2 threads: %d\n", share_value);
}

void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) share_value++;
}
