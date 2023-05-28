# Fundamental concepts

A waitqueue, in general, will cause a thread to sleep to wait a specific event.

# API

## DECLARE_WAIT_QUEUE_HEAD()

```c
DECLARE_WAIT_QUEUE_HEAD(wq)
```

Macro to declare a waitqueue

## init_waitqueue_head()

```c
wait_queue_head_t wq;
init_waitqueue_head(wq);
```

Init a waitqueue

## wait_event()

```c
wait_event(wq, condition);
```

``wait_event()`` will put the process/thread to sleep until the ``condition`` evaluates to ``true``. The ``condition`` is checked each time the waitqueue ``wq`` is woken up by calling the ``wake_up()``.

* ``wq``: the waitqueue to wait on
* ``condition``: a C expression for the event to wait for

``wake_up()`` has to be called after changing any variable that could change the result of the wait ``condition``.

## wait_event_timeout()

```c
wait_event_timeout(wq, condition, timeout);
```

Work like ``wait_event()``, with ``timeout`` to wait for condition

**Return**

* ``0``: if the ``condition`` evaluated is false after the timeout elapsed
* ``1``: if the ``condition`` evaluated is true

# Examples

## Character device to check for the value sent from userspace

Feature:

Create a character device with a waitqueue in a monitoring thread to check for the value sent from userspace. If that variable value is ``123`` (variable value is monitor by the ``waitqueue``), i.e waitqueue condition is true, the monitoring thread stops executing.

**Character device**: [waitqueue_variable_compare.c](waitqueue_variable_compare.c)

**Userspace**: ``echo 123 > /dev/fops_character_device``
## wait_event_timeout(): waitqueue for TIMEOUT

* Features like the [Character device example](#character-device-to-check-for-the-value-sent-from-userspace)
* Wait for ``TIMEOUT`` for condition evaluation (with [wait_event_timeout()](#wait_event_timeout))
* Call [init_waitqueue_head()](#init_waitqueue_head) to init waitqueue

```c
//Other operations are like waitqueue_variable_compare.c
wait_queue_head_t wq;
#define TIMEOUT 5000
int thread_function(void *kernel_data) {
	while(wait_event_timeout(wq, watch_var == 123, msecs_to_jiffies(5000)) == 0) 
		printk("watch_var is still not 123, but timeout elapsed!\n");
	printk("watch_var == %d; monitoring thread has finished execution\n", watch_var);
	return 0;
}

int device_init(void)
{
	init_waitqueue_head(&wq);//Init waitqueue before starting the monitoring thread
	if (create_character_device(DEVICE_NAME, DEVICE_CLASS, TOTAL_MINOR, BASE_MINOR, &dev_info, &fops)){
		printk("Unable to create character device %s\n", DEVICE_NAME);
		return -1;
	}

	kthread_1 = kthread_run(thread_function, NULL, "Thread monitoring variable sent from userspace");
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
## Wait queue in character device to blocked/suspended a calling userspace process

**Features**
* Create a character device with a waitqueue in **read()** file operation to check for the value sent from userspace, i.e by **write()** system call. Any **read()** system call from a userspace process will cause that process to be blocked/suspended.
* Sending ``123`` (variable value monitored by the ``waitqueue``), i.e waitqueue condition is true, to unblocked/unsuspended the userspace process

**Program**

* Chracter device to suspend the userspace process: [waitqueue_suspend_process.c](waitqueue_suspend_process.c)
* Userspace process: [userspace_process.c](userspace_process.c)

**Result**: 

In terminal 1, run ``userspace_process``:

```
$ ./userspace_process
PID 17764
Open /dev/fops_character_device successfully
(Blocking/suspending process PID 17764)
```

In ``dmesg``:

```
[  549.590021] open fops_character_device by userspace process with PID 17764
[  549.590045] read
[  549.590049] wait for watch_var == 0; userspace process 17764 will be blocked
```
In terminal 2, run ``echo 123 > /dev/fops_character_device``. Then ``userspace_process`` will be unblocked in terminal 1. In ``dmesg``:

```
[  572.458572] open fops_character_device by userspace process with PID 17764
[  572.458623] write data: 123

[  572.458627] watch_var is now 123
[  572.458651] close
[  572.458658] watch_var == 123; userspace process with PID 17764 is unblocked
[  572.459049] close
```