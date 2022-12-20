# Sending and receiving a single message in a message queue

## Send message to a message queue

Create a queue if not existed or get the ``msqid`` key if that message queue has already existed with flag ``0666``.
Then send message to that queue.

```c
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define KEY                 2//Set the key value number to any int number when creating
#define MSG_SIZE            100
#define MSG_TYPE            1

/*
    Set unused message flag to be any value for those 2 cases:
    *  The number of bytes already on the queue is equal to msg_qbytes
    *  The total number of messages on all queues system-wide is 
       equal to the system-imposed limit
*/
#define UNUSED_MSG_FLAG 0

struct msgp {
    long msgtype;
    char data[MSG_SIZE];
} msgbuf;

int main(){
    int msqid = msgget(KEY, IPC_CREAT|0666);
    if (msqid >= 0){
        msgbuf.msgtype = MSG_TYPE;
        strcpy(msgbuf.data, "Message queue data");
        if (!msgsnd(msqid, &msgbuf, MSG_SIZE, UNUSED_MSG_FLAG)){
            printf("Send message in message queue successfully\n");
        } else printf("Unable to send message in message queue\n");
    } else {
        printf("Unable to get msqid\n");
        
    }
}
```

**Result**

Run that program for the first time:

```
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x00000002 32769      tranphucvi 666        100          1      
```

A new message queue with key ID ``2`` is created with 1 message inside it. ``used-bytes`` is ``100`` as ``char data[MSG_SIZE]``.

Run that program for the 2nd time:

```
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x00000002 32769      tranphucvi 666        200          2  
```

## Receive message from message queue

Get the ``msqid`` from an existed message queue then read that message out

```c
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define KEY                 2//Set the key value number to any int number when creating
#define MSG_SIZE            100
#define MSG_TYPE            1

/*
    Set unused message flag to be any value for those 2 cases:
    *  The number of bytes already on the queue is equal to msg_qbytes
    *  The total number of messages on all queues system-wide is 
       equal to the system-imposed limit
*/
#define UNUSED_MSG_FLAG 0

struct msgp {
    long msgtype;
    char data[MSG_SIZE];
} msgbuf;

int main(){
    int msqid = msgget(KEY, IPC_CREAT|0666);
    if (msqid >= 0){
        msgrcv(msqid, &msgbuf, MSG_SIZE, MSG_TYPE, UNUSED_MSG_FLAG);
        printf("Message inside message queue: %s\n", msgbuf.data);
    } else {
        printf("Unable to get msqid\n");
        
    }
}
```

As this is the operation on the queue, every timne receiving the message from the message queue, its total message will be decreased by ``1``.

# Sending and receiving messages with multiple types in a message queue

## Send 2 message with 2 types to a message queue

```c
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define KEY                     123//Set the key value number to any int number when creating
#define MSG_SIZE                100
#define MSG_TYPE_1              1
#define MSG_TYPE_2              2

#define UNUSED_MSG_FLAG 0

struct msgp {
    long msgtype;
    char data[MSG_SIZE];
} msgbuf;

int main(){
    int msqid = msgget(KEY, IPC_CREAT|0666);
    if (msqid >= 0){

        //Send message to message queue of type 1
        msgbuf.msgtype = MSG_TYPE_1;
        strcpy(msgbuf.data, "Type 1: Send message queue data");
        if (!msgsnd(msqid, &msgbuf, MSG_SIZE, UNUSED_MSG_FLAG)){
            printf("Send message of type 1 in message queue successfully\n");
        } else printf("Unable to send message in message queue\n");

        //Send message to message queue of type 2
        msgbuf.msgtype = MSG_TYPE_2;
        strcpy(msgbuf.data, "Type 2: Send message queue data");
        if (!msgsnd(msqid, &msgbuf, MSG_SIZE, UNUSED_MSG_FLAG)){
            printf("Send message of type 2 in message queue successfully\n");
        } else printf("Unable to send message in message queue\n");
    } else {
        printf("Unable to get msqid\n");
        
    }
}
```

## Receive message with multiple types from message queue

```c
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define KEY                     123//Set the key value number to any int number when creating
#define MSG_SIZE                100
#define MSG_TYPE_1              1
#define MSG_TYPE_2              2

#define UNUSED_MSG_FLAG 0

struct msgp {
    long msgtype;
    char data[MSG_SIZE];
} msgbuf;

int main(){
    int msqid = msgget(KEY, IPC_CREAT|0666);
    if (msqid >= 0){
        //Receive message of type 1
        msgrcv(msqid, &msgbuf, MSG_SIZE, MSG_TYPE_1, UNUSED_MSG_FLAG);
        printf("Message of type 1 inside message queue: %s\n", msgbuf.data);

        //Receive message of type 2
        msgrcv(msqid, &msgbuf, MSG_SIZE, MSG_TYPE_2, UNUSED_MSG_FLAG);
        printf("Message of type 2 inside message queue: %s\n", msgbuf.data);
    } else {
        printf("Unable to get msqid\n");
        
    }
}
```

# Remove a message queue

To remove the message queue created above (with ID ``32769``): ``ipcrm -q 32769``

To remove by ``msgctl()``:

```c
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define KEY                 2//Set the key value number to any int number when creating

int main(){
    int msqid = msgget(KEY, IPC_CREAT|0666);
    if (msqid >= 0){
        msgctl(msqid, IPC_RMID, NULL);
    } else {
        printf("Unable to get msqid\n");        
    }
}
```
