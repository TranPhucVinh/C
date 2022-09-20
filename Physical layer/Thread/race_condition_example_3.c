#include <stdio.h>
#include <pthread.h>

#define RANGE 	10000

void *func_thread(void *ptr);
int share_value = 0;
int t1 = 1;
int t2 = 2;

int main()
{  
	pthread_t thread_1, thread_2;

	pthread_create(&thread_1, NULL, func_thread, &t1);
	pthread_create(&thread_2, NULL, func_thread, &t2);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	printf("share_value %d\n", share_value);
}

void *func_thread(void *ptr){
	int option;
    option = *(int*)ptr;
    int i;
    for (i = 0; i < RANGE; i++)
    {
        if (option == 1)
        {
            share_value++;
        }
        else
        {
            share_value--;
        }
    }
	return 0;
}