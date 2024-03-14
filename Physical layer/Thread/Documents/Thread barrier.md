Thread barrier will stop the execution of all threads waiting at it until there are enough number of threads this thread barrier specifies waiting.
# Use thread barrier to block all the threads when not having enough threads are created

```c
#include <stdio.h>
#include <pthread.h>

#define TOTAL_THREADS           2
#define THREAD_BARRIERS_NUMBER  3
#define PTHREAD_BARRIER_ATTR    NULL // pthread barrier attribute

pthread_barrier_t barrier;

void *thread_func(void *ptr){
    printf("Waiting at the barrier as not enough %d threads are running ...\n", THREAD_BARRIERS_NUMBER);
    pthread_barrier_wait(&barrier);
    printf("The barrier is lifted, thread id %ld is running now\n", pthread_self());
}

int main()
{  
	pthread_t thread_id[TOTAL_THREADS];

    pthread_barrier_init(&barrier, PTHREAD_BARRIER_ATTR, THREAD_BARRIERS_NUMBER);
    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_create(&thread_id[i], NULL, thread_func, NULL);
    }

    // As pthread_join() will block the process until all the threads it specifed are finished, 
    // and there is not enough thread to wait at the barrier, so this process is blocked
    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_join(thread_id[i], NULL);
    }
    pthread_barrier_destroy(&barrier);
    printf("Thread barrier is lifted\n"); // This line won't be called as TOTAL_THREADS < THREAD_BARRIERS_NUMBER
}
```
**Result**:
```
Waiting at the barrier as not enough 3 threads are running ...
Waiting at the barrier as not enough 3 threads are running ...
// (main process is blocked as not having enough 3 threads)
// Line printf("Thread barrier is lifted\n") won't be reached
```
Change **TOTAL_THREADS** to **3** and the thread barrier is lifted:
```
Waiting at the barrier as not enough 3 threads are running ...
Waiting at the barrier as not enough 3 threads are running ...
Waiting at the barrier as not enough 3 threads are running ...
The barrier is lifted, thread id 140643372406528 is running now
The barrier is lifted, thread id 140643380799232 is running now
The barrier is lifted, thread id 140643389191936 is running now
Thread barrier is lifted
```
Based on the definition of **pthread_barrier_init()**, the thread barrier is only lifted when a **count** number of threads call **pthread_barrier_wait()** (we define **count = THREAD_BARRIERS_NUMBER** in this example). So with **TOTAL_THREADS = k*THREAD_BARRIERS_NUMBER**, only a number of ``THREAD_BARRIERS_NUMBER`` threads can pass the thread barrier at a time until all **TOTAL_THREADS** are passed. E.g with the program above:
```c
#define TOTAL_THREADS           4
#define THREAD_BARRIERS_NUMBER  2
```
**Result**:
```
Waiting at the barrier as not enough 2 threads are running ...
Waiting at the barrier as not enough 2 threads are running ...
The barrier is lifted, thread id 139948129941248 is running now
The barrier is lifted, thread id 139948138333952 is running now
Waiting at the barrier as not enough 2 threads are running ...
Waiting at the barrier as not enough 2 threads are running ...
The barrier is lifted, thread id 139948146726656 is running now
The barrier is lifted, thread id 139948121548544 is running now
Thread barrier is lifted
```
From that result, we can see that the first 2 threads pass the thread barrier, then the next 2 will.

With **TOTAL_THREADS = k*THREAD_BARRIERS_NUMBER + x**, then there will be x number of threads which won't pass the thread barrier as x < THREAD_BARRIERS_NUMBER so there is not enough THREAD_BARRIERS_NUMBER to call **pthread_barrier_wait()** to lift the barrier:

```
Waiting at the barrier as not enough 2 threads are running ...
Waiting at the barrier as not enough 2 threads are running ...
The barrier is lifted, thread id 140013853472512 is running now
The barrier is lifted, thread id 140013962241792 is running now
Waiting at the barrier as not enough 2 threads are running ...
Waiting at the barrier as not enough 2 threads are running ...
The barrier is lifted, thread id 140013953849088 is running now
The barrier is lifted, thread id 140013945456384 is running now
Waiting at the barrier as not enough 2 threads are running ...
// main process is blocked now as there is just only 1 thread left to call pthread_barrier_wait(), while thread barrier needs 2 thread to call this function so that it can be lifted.
// Line printf("Thread barrier is lifted\n") won't be reached
```
# Use thread barrier to suspend and resume a thread
Feature: Suspend a thread when reaching a specific value then resume that thread by another thread

Program: [suspend_and_resume_threads_by_thread_barrier](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/suspend_and_resume_threads_by_thread_barrier.c)
# API
## pthread_barrier_init()
```cpp
int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned count);
```
* **count**: the number of threads that must call **pthread_barrier_wait()** before any of them successfully return from the call. count must be greater than 0
## pthread_barrier_destroy()
```c
int pthread_barrier_destroy(pthread_barrier_t *barrier);
```
The ``pthread_barrier_destroy()`` function shall destroy the barrier referenced by barrier and release any resources used by the barrier.
