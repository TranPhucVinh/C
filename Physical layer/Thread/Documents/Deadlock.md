# Deadlock
Deadlock happens when a process or thread remains indefinitely unable to change its state because:
* Resources requested by it are being used by another process that itself is waiting
* It waits infinitely for the other process to take action

## Try to lock a mutex 2 times to create deadlock

With program [mutex_pthread_mutex_lock.c](../src/mutex_pthread_mutex_lock.c) to use a mutex to increase a shared value, if calling pthread_mutex_lock() 2 times as trying to lock the mutex, program will **hang infinitely** as there is no more mutex left in the process to be locked:

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
## Deadlock doesn't occur when using a mutex for 2 threads to print odd and even numbers respectively

**Program**: [deadlock_with_mutex_for_threads_print_odd_and_even_numbers.c](../src/deadlock_with_mutex_for_threads_print_odd_and_even_numbers.c)

**Result**: Odd and even numbers are printed out from 7 to 1. However there will times ``odd number: 7`` is printed first and times when ``even number: 7`` is printed first
```
Odd number: 7
...
```

```
Even number: 7
...
```
## Deadlock when using SIGSTOP and SIGCONT to suspend and resume a thread
In this program, suspend_thread_func() is suspended by SIGSTOP signal and we expect resume_thread_func() to continue suspend_thread_func() by SIGCONT. However, this is wrong and causes deadlock because SIGSTOP suspends the whole process, not a single thread inside that process.

**Program**: [deadlock_with_sigstop_and_sigcont.c](../src/deadlock_with_sigstop_and_sigcont.c)

**Result**:

```
user@hostname:~/workspace$ ./a.out
number 1
number 2
number 3
Task is suspended

[1]+  Stopped                 ./a.out
```

When you send a SIGSTOP to thread ID ``suspend_thread`` inside ``suspend_thread_func``, the thread is halted. But once halted, it cannot process any further code, meaning it can’t resume on its own.

# Recursive mutex
Recursive mutex is a mutex that may be locked multiple times by the same process/thread, without causing a deadlock.

In this example, where 2 threads count down from a number with thread_odd only prints odd numbers and thread_even only prints even numbers, and both of those threads are defined recursively, a recursive mutex is suggested to use to avoid deadlock.

Program: [recursive_mutex_threads_print_odd_and_even_numbers.c](../src/recursive_mutex_threads_print_odd_and_even_numbers.c)

# Spin lock

If a resource is locked, a thread that wants to access that resource may repetitively check whether the resource is available. During that time, the thread may loop and check the resource without doing any useful work. Suck a lock is termed as spin lock.
# Debug to discover deadlock
In order to debug to know if the system is in deadlock, we can use the Banker's algorithm and Wait-for graph.