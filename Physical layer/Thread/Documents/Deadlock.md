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
# Spin lock

If a resource is locked, a thread that wants to access that resource may repetitively check whether the resource is available. During that time, the thread may loop and check the resource without doing any useful work. Suck a lock is termed as spin lock.
