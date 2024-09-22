# Fundamental concepts
[Thread creation](Documents/Thread%20creation.md):
* Thead definition
* [An example to create a thread to print out a string](): [pthread_create()](Documents/Thread%20creation.md#pthread_create), [flow of a program running a single thread](Documents/Thread%20creation.md#programs-flow)
* pthread_self() and thread ID
* Concurrency and parallelism

[Thread with argument](Documents/Thread%20with%20argument.md) includes:
* [Get the parameter of the thread by passing a variable](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#get-the-parameter-of-the-thread-by-passing-a-variable)
* [Get return from threads and store to a variable in single thread and multiple threads](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#get-return-from-threads-and-store-to-a-variable)
* [Enter value for struct member using thread](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Fundamental%20concepts%20examples.md#enter-value-for-struct-member-using-thread)

# Inter-task communication
## Data exchange
* [Using global variable to share values between 2 threads](src/share_global_variables_between_2_threads.c)
## Synchronization
* [Race condition](Race%20condition)
* [Thread barrier](Thread%20barrier.md)
### Race condition
[Race condition document](Race%20condition) includes:
* [One thread function handler to increase a shared value](Documents/Race%20condition.md#one-thread-function-handler-to-increase-a-shared-value)
* [One thread function handler to increase and decrease a shared value](Race%20condition/README.md#one-thread-function-handler-to-increase-and-decrease-a-shared-value)
* [Accessing a shared variable between 2 thread function handlers](Race%20condition/README.md#accessing-a-shared-variable-between-2-thread-function-handlers)
* [Semaphore](Documents/Semaphore.md)
* [Mutex](Documents/Mutex.md)
* Deadlock, recursive mutex and spin lock
### Suspending and resuming thread

**Suspend a thread when reaching a specific value then resume that thread by another one** can be implemented by
* [mutex with condition variable](Documents/Mutex.md): [suspend a thread when reaching a specific value then resume that thread by another thread](src/suspend_and_resume_threads_by_mutex_and_cond.c)
* [Semaphore](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/suspend_and_resume_threads_by_semaphore.c)
* [Thread barrier](src/suspend_and_resume_threads_by_thread_barrier.c)

For efficient implementation, suspend and resume threads must be implemented with OOP. Check [the corresponding document in CPP](https://github.com/TranPhucVinh/Cplusplus/tree/master/Physical%20layer/Thread#suspend-and-resume-threads) for that implementation.

**Must not use pthread_kill() with SIGSTOP and SIGCONT to suspend and resume thread**: Although pthread_kill() can send signal between threads, SIGSTOP and SIGCONT are supported only for process, not thread so we can't use those 2 signals to suspend and resume threads.
# [API](API)
* Thread creation
* Inter-task communication
# [Application](Documents/Application.md)
* [Use multiple threads for calculation]()
* [Multithread HTTP server built on TCP API]()
