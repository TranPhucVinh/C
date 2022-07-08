## API

```c
#include <linux/sched/signal.h>

struct siginfo;
```

```c
int send_sig_info(int sig, struct kernel_siginfo *signinfo, struct task_struct *user_space_process)
```

``send_sig_info()`` will send response signal from kernel space to user space: function acts on three parameters:

**Parameters**:

* ``sig``: Signal number
* ``signinfo``
* ``user_space_process``: User space process to sent signal to

## Examples

### Signal communication between user space and kernel space

In user space, open a character device by a process. In kernel space, when that character device is opened (in ``dev_open``), it will send signal ``SIGUSR1`` as a response to the user space process that opens it. That user space process then handles that responsed signal by signal handler function.

User space program: [user_space_signal_handler.c](user_space_signal_handler.c)

Character device: [character_device_response_signal.c](character_device_response_signal.c)

Using ``cat /dev/fops_character_device``, the result on terminal will be **User defined signal 1**.

Using ``echo "Hello" > /dev/fops_character_device``, the current running terminal will then be closed immediately. If using signal ``SIGRTMIN+10`` (``44``), that issue still happens.