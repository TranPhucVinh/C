# One thread function handler to increase a shared value
Solve the [one thread function handler to increase a shared value issue](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Documents/Race%20condition.md#one-thread-function-handler-to-increase-a-shared-value) with mutex, even with multiple threads, not just 2 tasks:
## Use [pthread_mutex_lock()](API.md#pthread_mutex_lock)

**Program**: [mutex_pthread_mutex_lock.c](../src/mutex_pthread_mutex_lock.c)

**Result**: ``shared_value after executing 3 threads: 9000000``
## Using [pthread_mutex_trylock()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/API/Inter-task%20communication.md#pthread_mutex_trylock)

With [pthread_mutex_trylock()](../API/Mutex%20and%20semaphore.md#pthread_mutex_trylock), if fails to lock the mutex, the thread will handle other task, which results in failing to increase the shared value to the ``RANGE``:

```c
int lock_count = 0;
/* main() and other operations are like pthread_mutex_lock() example */
void *thread_function(void *ptr){
    if (!pthread_mutex_trylock(&lock)){
    	for (int i = 0; i < RANGE; i++) {      	
			shared_value++;
		} 
        pthread_mutex_unlock(&lock);
    } else {
        printf("Didn't get lock in %s, %d\n", (char*)ptr, lock_count);
        lock_count += 1;
    }
}   
```
**Result**
```
Didn't get lock in Thread 2, 0
Didn't get lock in Thread 3, 0
shared_value after executing 3 threads: 3000000
```
When using **pthread_mutex_trylock()** for every increment operation:
```c
int lock_count = 0;
/* main() and other operations are like pthread_mutex_lock() example */
void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
      	if (!pthread_mutex_trylock(&lock)){
			shared_value++;
			pthread_mutex_unlock(&lock);
		} else {
			printf("Didn't get lock in %s, %d\n", (char*)ptr, lock_count);
			lock_count += 1;
		}
   }   
}
```
**Result**

```
Didn't get lock in Thread 2, 0
Didn't get lock in Thread 1, 1
Didn't get lock in Thread 2, 2
Didn't get lock in Thread 2, 3
...

Didn't get lock in Thread 3, 244
Didn't get lock in Thread 2, 245
Didn't get lock in Thread 1, 117
...
shared_value after executing 3 threads: 8990896 // Expect: 9000000
```
**Problem solved**: [mutex_pthread_mutex_trylock.c](../src/mutex_pthread_mutex_trylock.c)

# Two threads run respectively

* **Use a simple boolean variable as a mutex to make 2 threads run respectively**: [simple_boolean_variable_as_mutex.c](../src/mutex_boolean_variable_as_mutex.c)
* **Use pthread mutex**: [mutex_to_lock_the_variables.c](../src/mutex_threads_run_respectively.c)

**Note**: In order to run multiple threads respectively, mutex can't be used, condtion variable must be used instead.
