#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define TOTAL_THREADS           4
#define THREAD_BARRIERS_NUMBER  3
#define PTHREAD_BARRIER_ATTR    NULL // pthread barrier attribute

typedef struct _thread_barrier
{
    int thread_barrier_number;
    int total_thread;
    pthread_mutex_t lock;
    bool flag;
} thread_barrier;

thread_barrier barrier;

void thread_barrier_init(thread_barrier *barrier, pthread_mutexattr_t *mutex_attr, int thread_barrier_number){
    pthread_mutex_init(&(barrier->lock), mutex_attr);

    barrier->total_thread = 0;
    barrier->thread_barrier_number = thread_barrier_number;
    barrier->flag = false;
}

void thread_barrier_wait(thread_barrier *barrier){
    bool local_sense = barrier->flag;
    if(!pthread_mutex_lock(&(barrier->lock))){
        barrier->total_thread += 1;
        local_sense = !local_sense;
        
        if (barrier->total_thread == barrier->thread_barrier_number){
            barrier->total_thread = 0;
            barrier->flag = local_sense;
            pthread_mutex_unlock(&(barrier->lock));
        } else {
            pthread_mutex_unlock(&(barrier->lock));
            while (barrier->flag != local_sense); // wait for flag
        }
    }
}

void thread_barrier_destroy(thread_barrier *barrier){
    pthread_mutex_destroy(&(barrier->lock));
}

void *thread_func(void *ptr){
    printf("thread id %ld is waiting at the barrier, as not enough %d threads are running ...\n", pthread_self(), THREAD_BARRIERS_NUMBER);
    thread_barrier_wait(&barrier);
    printf("The barrier is lifted, thread id %ld is running now\n", pthread_self());
}

int main()
{  
	pthread_t thread_id[TOTAL_THREADS];

    thread_barrier_init(&barrier, PTHREAD_BARRIER_ATTR, THREAD_BARRIERS_NUMBER);
    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_create(&thread_id[i], NULL, thread_func, NULL);
    }

    // As pthread_join() will block the process until all the threads it specifed are finished, 
    // and there is not enough thread to wait at the barrier, so this process is blocked
    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_join(thread_id[i], NULL);
    }

    thread_barrier_destroy(&barrier);
    printf("Thread barrier is lifted\n"); // This line won't be called as TOTAL_THREADS < THREAD_BARRIERS_NUMBER
}
