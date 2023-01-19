Message queue allows the process to exchange the data in the form of messages.

Command [ipcs](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Process/System%20V%20IPC.md#ipcs) is useful for checking the message queue information.

# API

## msgget()

```c
int msgget(key_t key, int msgflg);
```

Get a System V message queue identifier

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

# Implementations

* [Sending and receiving a single message in a message queue](Implementations.md#sending-and-receiving-a-single-message-in-a-message-queue)
* [Sending and receiving messages with multiple types in a message queue](Implementations.md#sending-and-receiving-messages-with-multiple-types-in-a-message-queue)
* [Remove a message queue](Implementations.md#remove-a-message-queue)
