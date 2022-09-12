## Fundamental concepts

Kernel threads have emerged from the need to run kernel code in process context. A kernel thread is a thread that only runs in kernel mode and has no user address space or other user attributes.

## API

To create a thread kernel, use ``kthread_create()``:

```c
#include <linux/kthread.h>

struct task_struct *kthread_create(int (*threadfn)(void *data), void *data, const char namefmt[], ...);
```

* ``threadfn``: function that will be run by the kernel thread
* ``data``: parameter to be sent to the function
* ``namefmt``: kernel thread name, as it is displayed in ``ps``/``top``. It can contain  sequences ``%d``, ``%s`` etc., which will be replaced according to the standard ``printf`` syntax

To start the kernel thread, call ``wake_up_process()``:

```c
#include <linux/sched.h>
int wake_up_process(struct task_struct *p);
```

``wake_up_process()`` will also wake up a specific process as it attempts to wake up the nominated process and move it to the set of runnable processes.

Return:

* ``1``: process was woken up
* ``0``: process was already running

Alternatively, you can use ``kthread_run()`` to create and run a kernel thread:

```c
struct task_struct * kthread_run(int (*threadfn)(void *data), void *data, const char namefmt[], ...);
```

To stop a thread use ``kthread_stop()`` function.

Function ``kthread_should_stop()`` returns non-zero value if there is a stop request submitted by the ``kthread_stop()`` function. ``kthread_stop()`` must be called inside ``cleanup_module()`` to avoid memory crashing in kernel space when ``rmmod`` the kernel module that has the infinite loop formed by ``kthread_should_stop()``.

``get_current()``: Get pointer to current task structure. This will return a pointer of type ``struct task_struct *``.

## Examples

Check [examples document](Examples.md)