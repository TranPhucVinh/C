**Example 1**: Create a thread to print out a string

```c
#include <stdio.h>
#include <pthread.h>

void *func_thread_1(void *ptr);

int main()
{  
	pthread_t thread_1;
	int thread1_return;

	thread1_return = pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_join(thread_1, NULL);
}

void *func_thread_1(void *ptr){
	printf("Hello, World !\n");
}
```

Using function ``delaySeconds()`` in ``System time``, delay the displayed string in the thread every 2 seconds:

```c
void *func_thread_1(void *ptr){
	
	while(1){
		printf("Hello, World !\n");
		delaySeconds(2);
	}
}
```

Get the parameter of the thread

```c
thread1_return = pthread_create(&thread_1, NULL, func_thread_1, 56);

void *func_thread_1(void *ptr){
	printf("Parameter is %d\n", ptr);
}
```

Get the parameter of the thread by passing a variable

```c
int number = 56;
thread1_return = pthread_create(&thread_1, NULL, func_thread_1, (void*)number);

void *func_thread_1(void *ptr){
	printf("Parameter is %d\n", ptr);//56
}
```