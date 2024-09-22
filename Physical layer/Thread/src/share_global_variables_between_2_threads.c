#include <stdio.h>
#include <pthread.h>

void *start_routine_thread_1(void *ptr);
void *start_routine_thread_2(void *ptr);

int a;
int main(void){
	pthread_t thread_id_1, thread_id_2;

	pthread_create(&thread_id_1, NULL, start_routine_thread_1, NULL);
    pthread_create(&thread_id_2, NULL, start_routine_thread_2, NULL);

	pthread_join(thread_id_1, NULL);
    pthread_join(thread_id_2, NULL);

	return 0;
}

void *start_routine_thread_1(void *ptr){
    a = 10;
	printf("Value a in thread 1 is: %d\n", a);
}

void *start_routine_thread_2(void *ptr){
	printf("Value a in thread 2 is: %d\n", a);
}
