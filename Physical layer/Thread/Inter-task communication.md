# Using global variable to share values between 2 threads

```c
#include <stdio.h>
#include <pthread.h>

void *start_routine_thread_1(void *ptr);
void *start_routine_thread_2(void *ptr);

int a;
int main(void){
	int start_routine_thread_return_1, start_routine_thread_return_2;
	pthread_t start_routine_thread_id_1, start_routine_thread_id_2;//pointer thread for HTTP client

	start_routine_thread_return_1 = pthread_create(&start_routine_thread_id_1, NULL, start_routine_thread_1, NULL);
    start_routine_thread_return_2 = pthread_create(&start_routine_thread_id_2, NULL, start_routine_thread_2, NULL);

	pthread_join(start_routine_thread_id_1, NULL);
    pthread_join(start_routine_thread_id_2, NULL);

	return 0;
}

void *start_routine_thread_1(void *ptr){
    a = 10;
	printf("Value a in thread 1 is: %d\n", a);
}

void *start_routine_thread_2(void *ptr){
	printf("Value a in thread 2 is: %d\n", a);
}
```
**Result**
```
Value a in thread 2 is: 10
Value a in thread 1 is: 10
```
