Thread barrier will stop the execution of all threads waiting at it until there are enough number of threads this thread barrier specifies waiting.
# API
## pthread_barrier_init()
```c
int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned count);
```
The ``pthread_barrier_init()`` function shall allocate any resources required to use the barrier referenced by barrier and shall initialize the barrier with attributes referenced by ``attr``.
* ``count``: specify the number of threads that must call ``pthread_barrier_wait()`` before any of them successfully return from the call. The value specified by count must be greater than zero.
## pthread_barrier_destroy()
```c
int pthread_barrier_destroy(pthread_barrier_t *barrier);
```
The ``pthread_barrier_destroy()`` function shall destroy the barrier referenced by barrier and release any resources used by the barrier. The effect of subsequent use of the barrier is undefined until the barrier is reinitialized by another call to ``pthread_barrier_init()``.

# Create the same number of threads specified by the thread barrier to pass the barrier
```c
#include <stdio.h>
#include <pthread.h>

#define THREAD_BARRIER		3
#define BARRIER_ATTRIBUTE	NULL

pthread_barrier_t barrier;

void *thread_func(void *ptr);

int main()
{  
	pthread_t thread_id[THREAD_BARRIER];
	pthread_barrier_init(&barrier, NULL, THREAD_BARRIER);
	for (int i = 0; i < THREAD_BARRIER; i++){
		pthread_create(&thread_id[i], NULL, thread_func, NULL);
	}
	
	for (int i = 0; i < THREAD_BARRIER; i++){
		pthread_join(thread_id[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	printf("Process finishes execution\n");
	return 0;
}

void *thread_func(void *ptr){
	printf("Waiting at the barrier ...\n");
	pthread_barrier_wait(&barrier);
	printf("Passed the barrier ...\n");
}
```
**Result**
```
Waiting at the barrier ...
Passed the barrier ...
Waiting at the barrier ...
Passed the barrier ...
Waiting at the barrier ...
Passed the barrier ...
```
If we create less thread than the number of threads the thread barrier specified, the process will be blocked by this thread barrier:
```C
// Create the threads less than 1 compared to the THREAD_BARRIER
for (int i = 0; i < THREAD_BARRIER-1; i++){
    pthread_create(&thread_id[i], NULL, thread_func, NULL);
}

for (int i = 0; i < THREAD_BARRIER-1; i++){
    pthread_join(thread_id[i], NULL);
}
```
**Result**
```
Waiting at the barrier ...
Waiting at the barrier ...
(then block permanently)
```
