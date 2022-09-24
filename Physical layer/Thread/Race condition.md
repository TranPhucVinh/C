## One thread function handler to increase a share value

```c
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
```
**Result**: ``share_value after executing 2 threads: 14736`` (Expected ``20000``)

With ``RANGE`` is less than ``10000``, that data race issue doesn't happen, as the time 2 tasks race to take the resouce ``share_value`` is short.

**Problem solved**

* [Using mutex](Mutex.md)
* [Using semaphore](Semaphore.md)

## One thread function handler to increase and decrease a shared value

In this case, we expect the shared value to be ``0``

Source code: [increase_and_decrease_a_shared_value.c](increase_and_decrease_a_shared_value.c)

**Result**: (Run multiple times)

```
share_value 1428
share_value -1106
share_value -167
share_value -178
share_value 0
share_value 0
share_value 0
share_value -1070
share_value -1098
share_value 5460
```

Solved that race condition issue by mutex: [increase_and_decrease_a_shared_value_mutex.c](increase_and_decrease_a_shared_value_mutex.c)

**Result**:

Race condition still happen

Run 1st time: ``share_value 10000``

Run 2nd time: ``share_value 0``

Run 3rd time: ``share_value -10000``

If putting ``pthread_mutex_trylock()`` and ``pthread_mutex_unlock()`` inside each condition like this, race condition issue can't be fixed:

```c
void *func_thread(void *ptr){
	int option;
    option = *(int*)ptr;
    int i;
    for (i = 0; i < RANGE; i++)
    {
        if (option == 1)
        {
			if (!pthread_mutex_trylock(&lock)){
				share_value++;
				pthread_mutex_unlock(&lock);
			}      
        }
        else
        {
			if (!pthread_mutex_trylock(&lock)){
				share_value--;
				pthread_mutex_unlock(&lock);
			}     
        }
    }
	return 0;
}
```
**Result**: (Run multiple times)
```
share_value -585
share_value -170
share_value -196
share_value -7513
share_value -704
share_value -450
share_value 91
```

## Accessing a shared variable between 2 thread function handlers

Thread issue:

```c
#include <stdio.h>
#include <pthread.h>

char displayed_string[30];

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

int main()
{
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_2, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
	printf("Thread 1\n");
	sprintf(displayed_string, "%s", "Hello, World !");	
}

void *func_thread_2(void *ptr){
	printf("%s\n", displayed_string);
	printf("Thread 2\n");
}
```

```
Thread 1

Thread 2
```

(Value of ``displayed_string`` hasn't been updated so it is empty. **This is the result from race condition**).

If change to:

```c
void *func_thread_2(void *ptr){	
	printf("Thread 2\n");
	printf("%s\n", displayed_string);
}
```

```
Thread 1
Thread 2
Hello, World !
```

Beside race condition, that issue also happens due to using ``printf()`` and ``sprintf()``. Use ``write()`` and ``memcpy()`` will minimize the race condition incidents (as the result from race condition still happen but very little)

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

char displayed_string[30];

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

char thread_1_str[] = "Thread 1\n";
char thread_2_str[] = "Thread 2\n";

int main()
{
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_2, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}

void *func_thread_1(void *ptr){
	write(STDOUT_FILENO, thread_1_str, sizeof(thread_1_str));
	memcpy(displayed_string, "Hello, World !\n", 15);
}

void *func_thread_2(void *ptr){
	write(STDOUT_FILENO, displayed_string, sizeof(displayed_string));
	write(STDOUT_FILENO, thread_2_str, sizeof(thread_1_str));
}
```

That issue can be solved by [using semaphore](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Semaphore.md#accessing-a-shared-variable-between-2-thread-function-handlers-issue).