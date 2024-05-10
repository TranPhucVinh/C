# Deadlock

If a process remains indefinitely unable to change its state because resources requested by it are being used by another process that itself is waiting, then the system is said to be **in a deadlock**.

## Try to lock a mutex 2 times to create deadlock

With program [mutex_pthread_mutex_lock.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/mutex_pthread_mutex_lock.c) to use a mutex to increase a shared value, if calling pthread_mutex_lock() 2 times as trying to lock the mutex, program will **hang infinitely** as there is no more mutex left in the process to be locked:

```c
void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if(!pthread_mutex_lock(&lock)){
            if(!pthread_mutex_lock(&lock)){
                shared_value += 1;
                pthread_mutex_unlock(&lock);
            } else printf("%s fails to lock\n", (char*)ptr);
		} else printf("%s fails to lock\n", (char*)ptr);
   }   
}
```
# Recursive mutex
Recursive mutex is a mutex that may be locked multiple times by the same process/thread, without causing a deadlock.

In this example, where 2 threads count down from a number with thread_odd only prints odd numbers and thread_even only prints even numbers, and both of those threads are defined recursively, a recursive mutex is mandatorily used.

Program: [recursive_mutex_threads_print_odd_and_even_numbers.c](../src/recursive_mutex_threads_print_odd_and_even_numbers.c)

# Spin lock

If a resource is locked, a thread that wants to access that resource may repetitively check whether the resource is available. During that time, the thread may loop and check the resource without doing any useful work. Suck a lock is termed as spin lock.
