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
## [Using global variable to share values between 2 threads](src/share_global_variables_between_2_threads.c)
## pthread doesn't have API for suspending and resuming thread

**Suspend a thread when reaching a specific value then resume that thread by another one** can be implemented by
* [mutex with condition variable](Documents/Mutex.md): [suspend a thread when reaching a specific value then resume that thread by another thread](src/suspend_and_resume_threads_by_mutex_and_cond.c)
* [Semaphore](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/src/suspend_and_resume_threads_by_semaphore.c)
* [Thread barrier](src/suspend_and_resume_threads_by_thread_barrier.c)

For efficient implementation, suspend and resume threads must be implemented with OOP. Check [the corresponding document in CPP](https://github.com/TranPhucVinh/Cplusplus/tree/master/Physical%20layer/Thread#suspend-and-resume-threads) for that implementation.

## [Race condition](Race%20condition)

[Race condition document](Race%20condition) includes:
* [One thread function handler to increase a shared value](Documents/Race%20condition.md#one-thread-function-handler-to-increase-a-shared-value)
* [One thread function handler to increase and decrease a shared value](Race%20condition/README.md#one-thread-function-handler-to-increase-and-decrease-a-shared-value)
* [Accessing a shared variable between 2 thread function handlers](Race%20condition/README.md#accessing-a-shared-variable-between-2-thread-function-handlers)
* [Semaphore](Documents/Semaphore.md)
* [Mutex](Documents/Mutex.md)
# [Thread barrier](Thread%20barrier.md)

# [API](API)
* Thread creation
* Inter-task communication
# Application

## Use multiple threads for calculation

[Use 2 threads to calculate the sum from 1 to 2147483646](src/sum_from_1_to_n.c). This example will take 3 seconds to perform while [the raw function call](https://github.com/TranPhucVinh/C/blob/master/Algorithms/sum_from_1_to_n.c) will take 5 seconds to execute.

Using 3 threads will cause overflow error when compiling:

```c
range_1.lower_range = 0;
range_1.upper_range = N/3;

range_2.lower_range = N/3 + 1;
range_2.upper_range = 2*N/3;

range_3.lower_range = 2*N/3 + 1;
range_3.upper_range = N;
```

Problem solve: 

```c
range_1.lower_range = 0;
range_1.upper_range = N/3;

range_2.lower_range = N/3 + 1;
range_2.upper_range = N/3 + N/3;

range_3.lower_range = N/3 + N/3 + 1;
range_3.upper_range = N;
```
## [Multithread HTTP server built on TCP API](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/HTTP%20server#multithread-http-server-built-on-tcp-api)
