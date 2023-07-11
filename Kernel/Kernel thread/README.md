# Fundamental concepts

Kernel threads have emerged from the need to run kernel code in process context. A kernel thread is a thread that only runs in kernel mode and has no user address space or other user attributes.
# [Fundamental concepts implementations](Fundamental%20concepts%20implementations.md)

* [Create a single kernel thread and send an int number as argument to it](Fundamental%20concepts%20implementations.md#create-a-single-kernel-thread-and-send-an-int-number-as-argument-to-it)
* [Print out a string every 1 second in a kernel thread](Fundamental%20concepts%20implementations.md#print-out-a-string-every-1-second-in-a-kernel-thread)

# [Race condition](Race%20condition.md)

* [One thread function handler to increase a shared value](Race%20condition.md#one-thread-function-handler-to-increase-a-shared-value)
* [One thread function handler to increase and decrease a shared value](Race%20condition.md#one-thread-function-handler-to-increase-and-decrease-a-shared-value)
* [Accessing a shared variable between 2 thread function handlers](Race%20condition.md#accessing-a-shared-variable-between-2-thread-function-handlers)

# [Mutex](Mutex.md)
* [Mutex for character device](Mutex.md#mutex-for-character-device)
* [Mutex for kernel thread race condition](Mutex.md#mutex-for-kernel-thread-race-condition)

# API

## kthread_create()

To create a thread kernel, use ``kthread_create()``:

```c
#include <linux/kthread.h>

struct task_struct *kthread_create(int (*threadfn)(void *data), void *data, const char namefmt[], ...);
```

* ``threadfn``: function that will be run by the kernel thread
* ``data``: parameter to be sent to the function
* ``namefmt``: kernel thread name, as it is displayed in ``ps``/``top``. It can contain  sequences ``%d``, ``%s`` etc., which will be replaced according to the standard ``printf`` syntax

## wake_up_process()

To start the kernel thread, call ``wake_up_process()``:

```c
#include <linux/sched.h>
int wake_up_process(struct task_struct *p);
```

``wake_up_process()`` will also wake up a specific process as it attempts to wake up the nominated process and move it to the set of runnable processes.

Return:

* ``1``: process was woken up
* ``0``: process was already running

## kthread_run()

Alternatively, you can use ``kthread_run()`` to create and run a kernel thread:

```c
struct task_struct * kthread_run(int (*threadfn)(void *data), void *data, const char namefmt[], ...);
```

```c
int init_module(void)
{
    kthread_1 = kthread_run(thread_function, &kernel_data, "kthread_1");
	if(kthread_1 != NULL){
		printk("kthread_1 was created and is running now!\n");
	}
	else {
		printk("kthread_1 could not be created!\n");
		return -1;
	}
    return 0;
}
```

## kthread_stop() and kthread_should_stop()

To stop a thread use ``kthread_stop()`` function.

Function ``kthread_should_stop()`` returns non-zero value if there is a stop request submitted by the ``kthread_stop()`` function. ``kthread_stop()`` must be called inside ``cleanup_module()`` to avoid memory crashing in kernel space when ``rmmod`` the kernel module that has the infinite loop formed by ``kthread_should_stop()``.

## get_current()

Get pointer to current task structure. This will return a pointer of type ``struct task_struct *``.

## mutex_lock()

```c
void mutex_lock(mutex);
```