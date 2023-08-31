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
# Wait for a message sent into the POSIX message queue
``mq_notify.c``
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <signal.h>
#include <errno.h>

#define MQ_NAME "/MQ_NAME"//Must have / as its 1st character

#define QUEUE_PERMISSION    0666
#define MSG_PRIOR           0

union sigval value;
struct sigevent sigevt;
void msg_queue_receive(union sigval val);

int main()
{  
    sigevt.sigev_notify = SIGEV_THREAD;
    sigevt.sigev_notify_function = msg_queue_receive;
    
    mqd_t mq_fd = mq_open(MQ_NAME, O_RDWR);
    if (mq_fd > 0){
        value.sival_int = mq_fd;
        sigevt.sigev_notify_function(value);
        mq_notify(mq_fd, &sigevt);
    } else printf("Unable open %s\n", MQ_NAME);
}

void msg_queue_receive(union sigval val){
    char recv_buf[50];
    int mq_fd = val.sival_int;
    if (mq_receive(mq_fd, recv_buf, sizeof(recv_buf), MSG_PRIOR) > -1){
        printf("Received message: %s\n", recv_buf);
    } else {
        printf("Unable to receive message %d\n", errno);
    }
}
```
**Result**: When starting, this ``mq_notify`` program will be blocked as there is no message inside the POSIX message queue. Use the [Send message to a message queue]() program to send message to that POSIX message queue. ``mq_notify`` will read that string message out then stops.
