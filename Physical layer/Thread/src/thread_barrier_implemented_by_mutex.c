#include <stdio.h>
#include <pthread.h>

#define TOTAL_THREADS           4
#define THREAD_BARRIERS_NUMBER  3
#define PTHREAD_BARRIER_ATTR    NULL // pthread barrier attribute

typedef struct _thread_barrier
{
    int thread_barrier_number;
    pthread_mutex_t lock;
    int total_thread;
} thread_barrier;

thread_barrier barrier;

void thread_barrier_init(thread_barrier *barrier, pthread_mutexattr_t *mutex_attr, int thread_barrier_number){
    pthread_mutex_init(&(barrier->lock), mutex_attr);
    barrier->thread_barrier_number = thread_barrier_number;
}

void thread_barrier_wait(thread_barrier *barrier){
    if(!pthread_mutex_lock(&(barrier->lock))){
        barrier->total_thread += 1;
        pthread_mutex_unlock(&(barrier->lock));
    }

    while (barrier->total_thread < barrier->thread_barrier_number);\

    if(!pthread_mutex_lock(&(barrier->lock))){
        barrier->total_thread -= 1; // Decrease one thread as it has passed the thread barrier
        pthread_mutex_unlock(&(barrier->lock));
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
