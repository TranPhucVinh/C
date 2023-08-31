Message queue allows the process to exchange the data in the form of messages.

Message queue is the slowest IPC as when two process want to communicate by message queue, kernel has to make a linked list to send the data to it. By that, kernel has to do lots of work.

There are 2 types of message queue
* System V
* POSIX
  
# System V API

## msgget()

```c
int msgget(key_t key, int msgflg);
```

Get a System V message queue identifier or create it.

On success, ``msgget()`` returns the message queue identifier (a nonnegative integer) (``msqid`` listed in ``ipcs``).  On failure, ``-1`` is returned, and ``errno`` is set to indicate the error.

Create the a message queue with ``IPC_CREAT|IPC_EXCL`` flag (``IPC_CREAT|IPC_EXCL`` flag will be like ``O_CREAT|O_EXCL`` with ``open()``)

```c
#include <stdio.h>
#include <sys/msg.h>

#define RANDOM_KEY  1//Set the key value number to any int number when creating

int main(){
    int msqid = msgget(RANDOM_KEY, IPC_CREAT|IPC_EXCL);
    printf("msqid: %d\n", msqid);//msqid: 0
}
```

With ``msgget()``, set the key ``key_t`` to another random int value like ``RANDOM_KEY``. After running the program above, the result in [ipcs](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Process/System%20V%20IPC.md#ipcs) will be:

```
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x00000001 0          tranphucvi 0          0            0   
```

After creating (and sending message to message queue later), this message queue is only available as long as the system is still powered. That created message queue will lost when the system is powered off.

## msgsnd() and msgrcv()

```c
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```

The ``msgrcv()`` system call removes a message from the queue specified by ``msqid`` and places it in the buffer pointed to by ``msgp``.

The ``msgp`` argument is a pointer to caller-defined structure of the following general form:

```c
struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[1];    /* message data */
};
```

The ``mtext`` field is an array (or other structure) whose size is specified by ``msgsz``

The argument ``msgtyp`` specifies the type of message requested as follows:

* If ``msgtyp`` is 0, then the first message in the queue is read.
* If ``msgtyp`` is greater than 0, then the first message in the queue of type msgtyp is read, unless MSG_EXCEPT was specified in ``msgflg``, in which case the first message in the queue of type not equal to msgtyp will be read.
* If ``msgtyp`` is less than 0, then the first message in the queue with the lowest type less than or equal to the absolute value of msgtyp will be read.

## msgctl()

```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

Perform the control operation specified by ``cmd`` on the System V message queue with identifier ``msqid``.

# System V implementations

* [Sending and receiving a single message in a message queue](Implementations.md#sending-and-receiving-a-single-message-in-a-message-queue)
* [Sending and receiving messages with multiple types in a message queue](Implementations.md#sending-and-receiving-messages-with-multiple-types-in-a-message-queue)
* [Remove a message queue](Implementations.md#remove-a-message-queue)
# POSIX message queue API

With POSIX message queue, messages are transferred to and from a queue using [mq_send()]() and [mq_receive()](). When a process has finished using the queue, it closes it using [mq_close()](), and when the queue is no longer required, it can be deleted using [mq_unlink()](). A process can request asynchronous notification of the arrival of a message on a previously empty queue using [mq_notify()]().

Each message has an associated priority, and messages are always delivered to the receiving process highest priority first.

Message priorities range from ``0`` (**low**) to ``sysconf(_SC_MQ_PRIO_MAX) - 1`` (**high**).  On Linux, `sysconf(_SC_MQ_PRIO_MAX)`` returns ``32768``, but POSIX.1 requires only that an implementation support at least priorities in the range ``0`` to ``31``; some implementations provide only this range.
## Create and mount mqueue device file
In order to monitor the POSIX message queue by CLI like ipcs in System V, take those steps:
```sh
username@hostname:~$ sudo mkdir /dev/mqueue
username@hostname:~$ sudo mount -t mqueue mqueue /dev/mqueue
```
From now, all POSIX message queue can be found inside ``/dev/mqueue``
```sh
username@hostname:~$ cat /dev/mqueue/message_queue_name # View property of a message queue
QSIZE:0          NOTIFY:0     SIGNO:0     NOTIFY_PID:0  
```
## Compile and libraries
Compile with external library ``rt`` (realtime): ``gcc main.c -lrt``.
```c
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
```
## mq_open() and struct mq_attr
```c
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
```

Creates a new POSIX message queue or opens an existing queue.
**Parameters**:
* ``name``: Name of the POSIX message queue, its first character must start with ``/``
**Return**:

* On success, mq_open() returns a message queue descriptor
* On error, ``-1`` is returned

```c
struct mq_attr {
    long mq_flags;       /* Flags (ignored for mq_open()) */
    long mq_maxmsg;      /* Max. numbers of messages on queue */
    long mq_msgsize;     /* Max. message size (bytes) */
    long mq_curmsgs;     /* Numbers of messages currently in queue (ignored for mq_open()) */
};
```
## mq_send()
```c
int mq_send(mqd_t mqdes, const char msg_ptr[.msg_len], size_t msg_len, unsigned int msg_prio);
```
* ``msg_prio``: specify the priority of this message.  Messages are placed on the queue in decreasing order of priority, with newer messages of the same priority being placed after older messages with the same priority

Return: On success, mq_send() returns ``0``; on error, ``-1`` is returned.
## mq_receive()
```c
ssize_t mq_receive(mqd_t mqdes, char msg_ptr[.msg_len], size_t msg_len, unsigned int *msg_prio);
```
**Return**: On success, mq_receive() returns the number of bytes in the received message. on error, ``-1`` is returned
## mq_notify()
```c
int mq_notify(mqd_t mqdes, const struct sigevent *sevp);
```
Register for notification when a message is available inside the POSIX message queue.

Please note that [struct sigevent](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Signal/API.md#struct-sigevent) in this function is always used as the argument of an API.

**Return**: On success ``mq_notify()`` returns ``0``; on error, ``-1`` is returned, with errno set to indicate the error.
# POSIX message queue implementations
* [Create a POSIX message queue]()
* [Send message to a message queue]()
* [Receive message from a message queue]()
* [Wait for a message sent into the POSIX message queue by mq_notify()](POSIX%20message%20queue%20implementations.md#wait-for-a-message-sent-into-the-posix-message-queue)
