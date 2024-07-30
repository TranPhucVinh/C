# Get the parameter of the thread by passing a variable

**Wrong operation that gives right result**

```c
void *func_thread_1(void *ptr);

int main() {  
    pthread_t thread_1;
	int number = 56;
    pthread_create(&thread_1, NULL, func_thread_1, &number);
    pthread_join(thread_1, NULL);
}

void *func_thread_1(void *ptr){
	printf("Parameter is %d\n", *((int*)ptr));//56
}
```

**Result**

```
Parameter is 56
```

Parameter ``number`` must have garbage value as it is the local variable inside ``main()`` but this example actually return its correct value. That happens as ``number`` can still keep because both ``func_thread_1()`` and ``main()`` will end their execution at the same time.

When using 2 tasks with local variable, the garbage value will be received

```c
void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);
pthread_t thread_1_create;
pthread_t thread_2_create;
int main()
{
	pthread_create(&thread_1_create, NULL, func_thread_1, NULL);
	sleep(5);
}

void *func_thread_1(void *ptr){
	int number = 56;
	pthread_create(&thread_2_create, NULL, func_thread_2, &number);
}

void *func_thread_2(void *ptr){
	sleep(1);
	printf("Parameter is %d\n", *((int*)ptr));
}
```
**Result**
```
Parameter is 32719 (garbage value)
```

**Problem solve**: 

Solution 1: Use ``static``

```c
void *func_thread_1(void *ptr) {
	static int number = 56;
	pthread_create(&thread_2_create, NULL, func_thread_2, &number);
}
```

Solution 2: Use ``malloc()``

```c
void *func_thread_1(void *ptr) {
	int *number = (int*)malloc(sizeof(int));
	*number = 123;
	pthread_create(&thread_2_create, NULL, func_thread_2, number);
}
```

# Get return from threads and store to a variable

## Single thread

**Using pointer of pointer**

```c
int main() {  
    int **thread_1_return;
	pthread_t thread_1;

    thread_1_return = (int**) malloc(sizeof(int**));
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_join(thread_1, (void**)thread_1_return);
    printf("value: %d\n", **thread_1_return);//123
}

void *func_thread_1(void *ptr){
	int *number = (int*) malloc (sizeof(int));
    *number = 123;
	return number;
}
```

**Using pointer**

```c
int *thread_1_return;
pthread_join(thread_1, (void**)&thread_1_return);
printf("value: %d\n", *thread_1_return);//123
//Other operations like above
```

## Multiple threads

Using pointer:

```c
int main()
{  
    int *thread_1_return, *thread_2_return;
	pthread_t thread_1, thread_2;

	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_1, NULL);

	pthread_join(thread_1, (void**)&thread_1_return);
	pthread_join(thread_2, (void**)&thread_2_return);

    printf("value: %d\n", *thread_1_return);//123
	printf("value: %d\n", *thread_2_return);//123
	free(thread_1_return);
	free(thread_2_return);
}

void *func_thread_1(void *ptr){
	int *number = (int*) malloc (sizeof(int));
    *number = 123;
	return number;
}
```

Using pointer to pointer:

```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *func_thread_1(void *ptr);

int main()
{  
    int **thread_1_return, **thread_2_return;
    thread_1_return = (int**)malloc(sizeof(int*));
    thread_2_return = (int**)malloc(sizeof(int*));

	pthread_t thread_1, thread_2;

	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_1, NULL);

	pthread_join(thread_1, (void**)thread_1_return);
	pthread_join(thread_2, (void**)thread_2_return);
    printf("value: %d\n", **thread_1_return);//123
	printf("value: %d\n", **thread_2_return);//123
	free(*thread_1_return);
	free(*thread_2_return);
}

void *func_thread_1(void *ptr){
	int *number = (int*) malloc (sizeof(int));
    *number = 123;
	return number;
}
```

# Enter values for struct member using thread 

<details>
	
```cpp
#include <stdio.h>
#include <pthread.h>

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
</details>
