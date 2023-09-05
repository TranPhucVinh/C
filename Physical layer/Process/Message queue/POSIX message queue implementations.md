# Create a POSIX message queue
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>

#define MQ_NAME "/MQ_NAME"// Must have / as its 1st character

#define MAX_MESSAGE         10
#define MAX_MSG_SIZE        10
#define QUEUE_PERMISSION    0666

struct mq_attr msgq_attr;//Message queue attribute

int main()
{  
    msgq_attr.mq_flags = 0;
    msgq_attr.mq_maxmsg = MAX_MESSAGE;
    msgq_attr.mq_msgsize = MAX_MSG_SIZE;
    msgq_attr.mq_curmsgs = 0;

    mqd_t mq_fd = mq_open(MQ_NAME, O_CREAT|O_EXCL, QUEUE_PERMISSION, &msgq_attr);
    printf("%d %d\n", mq_fd, errno);
}
```
# Remove a POSIX message queue by mq_unlink()
```c
#define MQ_NAME "/MQ_NAME"// Must have / as its 1st character

int main()
{  
    int mq_fd = mq_unlink(MQ_NAME);
    if (!mq_fd) printf("Remove %s successfully\n", MQ_NAME);
    else if (mq_fd == -1) printf("Unable to remove %s\n", MQ_NAME);
}
```
# Send message to a message queue
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>

#define MQ_NAME "/MQ_NAME"//Must have / as its 1st character

#define QUEUE_PERMISSION    0666
#define MSG_PRIOR           0

int main()
{  
    mqd_t mq_fd = mq_open(MQ_NAME, O_RDWR);
    if (mq_fd > 0){
        char snd_str[] = "012345678";//10 character
        if (!mq_send(mq_fd, snd_str, sizeof(snd_str), MSG_PRIOR)){
            printf("Message delivered successfully\n");
        } else {
            printf("Unable to deliver message\n");
            if (errno == 90) printf("Sent message is longer than the MAX_MSG_SIZE\n");
        }
    } else printf("Unable open %s\n", MQ_NAME);
}
```
# Receive message from a message queue
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>

#define MQ_NAME "/MQ_NAME"//Must have / as its 1st character

#define QUEUE_PERMISSION    0666
#define MSG_PRIOR           0

int main()
{  
    mqd_t mq_fd = mq_open(MQ_NAME, O_RDWR);
    if (mq_fd > 0){
        char recv_buf[50];
        if (mq_receive(mq_fd, recv_buf, sizeof(recv_buf), MSG_PRIOR) > -1){
            printf("Received message: %s\n", recv_buf);
        } else {
            printf("Unable to receive message %d\n", errno);
        }
    } else printf("Unable open %s\n", MQ_NAME);
}
```
# Send and receive message from a message queue with other data type like int, float
As ``mq_send()`` and ``mq_receive()`` allow sending/receiving char* by default, typecasting the data sent/receive in those 2 functions to ``(*char)`` for other data type.
``send_int.c``
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>

#define MQ_NAME "/MQ_NAME"//Must have / as its 1st character

#define QUEUE_PERMISSION    0666
#define MSG_PRIOR           0

int main()
{  
    mqd_t mq_fd = mq_open(MQ_NAME, O_RDWR);
    if (mq_fd > 0){
        int snd_int = 13579;
        if (!mq_send(mq_fd, (char*)&snd_int, sizeof(snd_int), MSG_PRIOR)){
            printf("Message delivered successfully\n");
        } else {
            printf("Unable to deliver message\n");
            if (errno == 90) printf("Sent message is longer than the MAX_MSG_SIZE\n");
        }
    } else printf("Unable open %s\n", MQ_NAME);
}
```
``recv_int.c``
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>

#define MQ_NAME "/MQ_NAME"//Must have / as its 1st character

#define QUEUE_PERMISSION    0666
#define MSG_PRIOR           0

/*
    This macro will expand the read size for the buffer to receive from the message queue
    Please note that although receving only one int number from the send_int process,
    the received buffer size allocated by mq_receive() must be bigger than its data type
    at least 3 times, i.e 4 byte*3 for int type. This conclusion comes from manual testing
*/ 

#define EXPANDED_RD_SIZE    3
int main()
{  
    mqd_t mq_fd = mq_open(MQ_NAME, O_RDWR);
    if (mq_fd > 0){
        int recv_int; 
        // Simply type-casting mq_receive()
        if (mq_receive(mq_fd, (char*)&recv_int, sizeof(recv_int)*EXPANDED_RD_SIZE, MSG_PRIOR) > -1){
            printf("Received message: %d\n", recv_int);
        } else {
            printf("Unable to receive message %d\n", errno);
        }
    } else printf("Unable open %s\n", MQ_NAME);
}
```
**For float number**: ``send_float.c``
```c
float float_number = 135.79;
if (!mq_send(mq_fd, (char*)&float_number, sizeof(float_number), MSG_PRIOR)){
    printf("Message delivered successfully\n");
} //...
```
``recv_float.c``
```c
float recv_float; 
if (mq_receive(mq_fd, (char*)&recv_float, sizeof(recv_float)*EXPANDED_RD_SIZE, MSG_PRIOR) > -1){
    printf("Received message: %lf\n", recv_float);
} //...
```
# Wait for a message sent into the POSIX message queue
**Program**: [mq_notify.c](mq_notify.c)

**Result**: When starting, this ``mq_notify`` program will be blocked as there is no message inside the POSIX message queue. Use the [Send message to a message queue]() program to send message to that POSIX message queue. ``mq_notify`` will read that string message out then stops.
