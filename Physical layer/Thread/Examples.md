### Example 1

Create a thread to print out a string

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
	printf("thread_1 finish executing\n");
}

void *func_thread_1(void *ptr){
	printf("Hello, World !\n");
}
```

**Result**

```
Hello, World !
thread_1 finish executing
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

Get the parameter of the thread by passing a variable

```c
int number = 56;
thread_1_create = pthread_create(&thread_1, NULL, func_thread_1, &number);

void *func_thread_1(void *ptr){
	printf("Parameter is %d\n", *((int*)ptr));//56
}
```
Get return from a thread and store to a variable:

```c
int main()
{  
    int **thread_1_return;
	pthread_t thread_1;
	int thread_1_create;

	thread_1_create = pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_join(thread_1, (void**)thread_1_return);
    printf("value: %d\n", **thread_1_return);
    free(thread_1_return);
}

void *func_thread_1(void *ptr){
	int *array = (int*) malloc (sizeof(int));
    *array = 123;
	return array;
}
```
### Example 2

Enter value for struct member using thread 

```c
#include<stdio.h>
#include<pthread.h>

struct databaseNode {
	int id;
	char stringValue[50];
} databaseNode0;

void *start_routine_thread(void *ptr);

int main(void){
	int start_routine_thread_return;
	pthread_t start_routine_thread_id;//pointer thread for HTTP client

	start_routine_thread_return = pthread_create(&start_routine_thread_id, NULL, start_routine_thread, NULL);//HTTP client thread

	pthread_join(start_routine_thread_id, NULL);

	printf("databaseNode0 has id %d with string value %s \n", databaseNode0.id, databaseNode0.stringValue);

	return 0;
}

void *start_routine_thread(void *ptr){
	printf("Enter ID: ");
	scanf("%d", &databaseNode0.id);
	getc(stdin); //To handle with issue scanf before fgets

	printf("Enter string value: ");
	fgets(databaseNode0.stringValue, 50, stdin); //fgets allow to enter value with space
}
```
### Example 3

Sharing values between 2 threads

```c
#include<stdio.h>
#include<pthread.h>

void *start_routine_thread_1(void *ptr);
void *start_routine_thread_2(void *ptr);

int a;
int main(void){
	int start_routine_thread_return_1, start_routine_thread_return_2;
	pthread_t start_routine_thread_id_1, start_routine_thread_id_2;//pointer thread for HTTP client

	start_routine_thread_return_1 = pthread_create(&start_routine_thread_id_1, NULL, start_routine_thread_1, NULL);//HTTP client thread
    start_routine_thread_return_2 = pthread_create(&start_routine_thread_id_2, NULL, start_routine_thread_2, NULL);//HTTP client thread

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
