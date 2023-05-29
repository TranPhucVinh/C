# Character device to check for the value sent from userspace

**Feature**

Create a character device with a waitqueue in a monitoring thread to check for the value sent from userspace. If that variable value is ``123`` (variable value is monitor by the ``waitqueue``), i.e waitqueue condition is true, the monitoring thread stops executing.

**Character device**: [waitqueue_variable_compare.c](waitqueue_variable_compare.c)

**Userspace**: ``echo 123 > /dev/fops_character_device``

# wait_event_timeout(): waitqueue for TIMEOUT

* Features are like the [Character device example](#character-device-to-check-for-the-value-sent-from-userspace)
* Wait for ``TIMEOUT`` for condition evaluation (with [wait_event_timeout()](README.md#wait_event_timeout))
* Call [init_waitqueue_head()](README.md#init_waitqueue_head) to init waitqueue

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
# Wait queue in character device to blocked/suspended a calling userspace process

## wait_event()

### Features
* Create a character device with a waitqueue in **read()** file operation to check for the value sent from userspace, i.e by **write()** system call. Any **read()** system call from a userspace process will cause that process to be blocked/suspended.
* Sending ``123`` (variable value monitored by the ``waitqueue``), i.e waitqueue condition is true, to unblocked/unsuspended the userspace process

### Program

* Chracter device to suspend the userspace process: [waitqueue_suspend_process.c](waitqueue_suspend_process.c)
* Userspace process: [userspace_process.c](userspace_process.c)

### Result

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

While ``userspace_process`` is blocking/suspending, it can't be killed or interrupt (e.g: by [kill](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Process/Signal.md#kill) command:

```sh
$ kill 17764 # This won't kill PID 17764
$ kill -SIGKILL 17764 # This won't kill PID 17764
$ kill -SIGINT 17764 #  This won't interrupt PID 17764
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
## wait_event_interruptible() and wait_event_killable()

**Features** are like the [wait_event() implementation](#wait_event-1), but the blocking/suspending userspace process can be interrupted/killed by SIGINT/SIGKILL signal.

```c
//Other operations are like waitqueue_suspend_process.c
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	//Other operations are like waitqueue_suspend_process.c
	wait_event_interruptible(wq, watch_var == 123);
    // Same result: wait_event_killable(wq, watch_var == 123);

    printk("watch_var == %d; userspace process %d is unblocked\n", watch_var, userspace_process->pid);
	return 0;
}

ssize_t dev_write(struct file*filep, const char __user *buf, size_t len, loff_t *offset)
{
	//Other operations are like waitqueue_suspend_process.c
	wake_up_interruptible(&wq);
	// wake_up(&wq) for wait_event_killable()
	return sizeof(data);
}
```

While ``userspace_process`` is blocking, send SIGKILL signal: ``kill 4863``
```
PID 4863 // userspace process is blocking 
Open /dev/fops_character_device successfully // userspace process is blocking 
Terminated // After receiving kill 4863
```

With ``kill -SIGKILL 4863``, the result is **Killed**:

```
PID 4863 // userspace process is blocking 
Open /dev/fops_character_device successfully // userspace process is blocking 
Killed // After receiving kill -SIGKILL 4863
```

With ``kill -SIGINT 4863``, the result is **(NULL)**:

```
PID 4863 // userspace process is blocking 
Open /dev/fops_character_device successfully // userspace process is blocking 
(NULL) // After receiving kill -SIGINT 4863
```
**dmesg**
```
[ 1555.943495] Create character device fops_character_device successfully
[ 1566.937385] open fops_character_device by userspace process with PID 4725
[ 1566.937410] read
[ 1566.937413] wait for watch_var == 0; userspace process 4725 will be blocked
[ 1586.409975] watch_var == 0; userspace process 4725 is unblocked
[ 1586.410292] close
```

# wait_event_interruptible_timeout()

**Features**, **testing** and **result** are like the [wait_event_interruptible() and wait_event_killable() implementation](#wait_event_interruptible-and-wait_event_killable), except using [wait_event_interruptible_timeout()](README.md#wait_event_interruptible_timeout) to notify the timeout message when condition check is not reached during timeout.

```c
ssize_t dev_read(struct file*filep, char __user *buf, size_t len, loff_t *offset)
{
	//Other operations are like waitqueue_suspend_process.c
	while(wait_event_interruptible_timeout(wq, watch_var == 123, msecs_to_jiffies(10000)) == 0) 
		printk("watch_var is still not 123, but timeout elapsed!\n");
	printk("watch_var == %d; userspace process %d is unblocked\n", watch_var, userspace_process->pid);
	return 0;
}
```