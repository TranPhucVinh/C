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
