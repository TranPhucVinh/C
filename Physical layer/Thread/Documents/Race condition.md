# One thread function handler to increase a shared value
Use one function handler in multiple threads to increase a shared value: [race_condition_multi_threads_increase_shared_value.c](../src/race_condition_multi_threads_increase_shared_value.c)

**Result**: ``share_value after executing 2 threads: 14736`` (Expected ``20000``)

With ``RANGE`` is less than ``10000``, that data race issue doesn't happen, as the time 2 tasks race to take the resouce ``share_value`` is short.

**Problem solved**

* [Using mutex](Mutex.md)
* [Using semaphore](Semaphore.md)

**Note**: For both mutex and semaphore solution, if putting a debug line like this inside the ``thread_function()``:
```c
void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) share_value++;
	printf("share_value %d", share_value);
}
```
**Result**:
```
7977229 #Thread 1
8736671 #Thread 2
9000000 #Thread 3
```
``7977229`` in thread 1 means its has already finished increasing from 1 to ``RANGE`` for share_value while thread 2 and thread 3 are still increasing. Same explanation for ``8736671`` in thread 2.
# One thread function handler to increase and decrease a shared value

In this case, we expect the shared value to be ``0``. Source code: [race_condition_increase_and_decrease_shared_value.c](../src/race_condition_increase_and_decrease_shared_value.c)

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
# Multiple threads run respectively
With 2 different thread functions handler in 2 threads have delay, we want those 2 threads to run respectively, as thread 1 finishes running then thread 2 start running: [race_condition_threads_run_respectively.c](../src/race_condition_threads_run_respectively.c)

**Result**:
```
Thead 1: 0
Thead 2: 0
Thead 2: 1
Thead 1: 1
...
```
# Accessing a shared variable between 2 thread function handlers

Use **write()** and **memcpy()** will minimize the race condition incidents (as the result from race condition still happen but very little): [race_condition_threads_run_respectively.c](../src/race_condition_access_shared_var_between_2_thread_func_handler.c)

**Result**

| Run 1st time | Run 2nd time |
| ------- |:------:|
| (Empty)<br>Thread 2 <br>Thread 1  <br>| Thread 1<br>Hello, World !<br>Thread 2|

That issue can be solved by [using semaphore](Semaphore.md#accessing-a-shared-variable-between-2-thread-function-handlers-issue).

# Producer and consumer problem

Given a buffer, i.e a shared variable, where the **producer thread** writes data to it for every TIME_INTERVAL seconds. The **main thread** as the **consumer thread** will pop out the data from that buffer to read, whenever that buffer isn't empty. The **main thread** simply uses a for loop to check for the available data of the buffer to read:

**Program**: [producer_consumer_simple_loop_check.c](../src/producer_consumer_simple_loop_check.c)

**Result**

```
Producer thread has produced: 1
Main thread has consumed: 1
Producer thread has produced: 1
Main thread has consumed: 2
Producer thread has produced: 1
Main thread has consumed: 3
```

This program wastes CPU time, because the main thread continually loops, checking the state of the shared variable. A **condition variable** remedies this problem. It allows a thread to sleep (wait) until another thread notifies (signals) it that it must do something (i.e., that some “condition” has arisen that the sleeper must now respond to).
