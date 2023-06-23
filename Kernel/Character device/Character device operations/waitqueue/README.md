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

``wake_up()`` must be called after changing any variable that could change the result of the ``condition`` of ``wait_event()``.

``wait_event()`` is marked with **TASK_UNINTERRUPTIBLE** state, i.e when the kernel module including this function causes the userspace process opening it to be blocked/suspended, signal SIGKILL or SIGINT can't be used to unblock/unsuspend it. Check [wait_event(): Wait queue in character device to blocked/suspended a calling userspace process](Implementations.md#wait_event) for that implementation.

## wait_event_timeout()

```c
wait_event_timeout(wq, condition, timeout);
```

Work like [wait_event()](#wait_event), with ``timeout`` (in **jiffies**) to wait for condition.

**Return**

* ``0``: if the ``condition`` evaluated is false after the timeout elapsed. Kernel module will then keep on waiting until ``condition`` is ``true``
* ``1``: if the ``condition`` evaluated is true

## wait_event_interruptible()

```c
wait_event_interruptible(wq, condition);
```
Work like [wait_event()](#wait_event) with wake function must be ``wake_up_interruptible()``

``wait_event_interruptible()`` is marked with **TASK_INTERRUPTIBLE** state. Userspace process with state **TASK_INTERRUPTIBLE** is waiting for some event. If a signal (can be any type SIGKILL, SIGINT, SIGUSR1,...) with is generated for a process in this state, then the operation is interrupted and the process is woken up by the delivery of a signal.

Check [wait_event_interruptible(): Wait queue in character device to blocked/suspended a calling userspace process](Implementations.md#wait_event_interruptible-and-wait_event_killable) for that implementation.
## wait_event_killable()
```c
wait_event_killable(wq, condition);
```
Work like [wait_event()](#wait_event) with wake function must be ``wake_up()``.
``wait_event_killable()`` is marked with **TASK_KILLABLE**. **TASK_KILLABLE** is added since kernel 2.6.25 to address the hanging process problem. When a suspending/blocking process receives a fatal signal (i.e., one that would kill the process), this process will wake up. Generally, the signal handling mechanism of ``wait_event_killable()``  works identically to [wait_event_interruptible()](#wait_event_interruptible).

Check [wait_event_killable(): Wait queue in character device to blocked/suspended a calling userspace process](Implementations.md#wait_event_interruptible-and-wait_event_killable) for that implementation.
## wait_event_interruptible_timeout()
```c
wait_event_interruptible_timeout(wq, condition, timeout);
```
Work like [wait_event_interruptible()](#wait_event_interruptible-and-wait_event_killable), with ``timeout`` (in **jiffies**) to wait for condition.
# Implementations
* [Character device to check for the value sent from userspace]()
* [wait_event_timeout(): waitqueue for TIMEOUT]()
* [Wait queue in character device to blocked/suspended a calling userspace process](): [wait_event()](), [wait_event_interruptible() and wait_event_killable()]()
* [wait_event_interruptible_timeout()]()