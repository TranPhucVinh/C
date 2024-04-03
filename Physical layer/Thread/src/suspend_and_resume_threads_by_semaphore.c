#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NO_PROC_SHARED 0 // Not share between processes
#define SEM_VAL	1

void *suspend_thread_func(void *ptr);
void *resume_thread_func(void *ptr);

int number = 0;

pthread_t suspend_thread, resume_thread;
sem_t bin_sem;// Binary semaphore

void resumeThread()
{ 
    sem_post(&bin_sem);
}

void suspendThread()
{ 
    // As sem_init with SEM_VAL = 1 so have to call sem_wait() 2 times to make it block
    if (!sem_wait(&bin_sem));
    if (!sem_wait(&bin_sem));

    // Set SEM_VAL = 0 so that just need to call sem_wait() 1 time to block the thread
}

int main(void){
    sem_init(&bin_sem, NO_PROC_SHARED, SEM_VAL);
	
	pthread_create(&suspend_thread, NULL, suspend_thread_func, NULL);
    pthread_create(&resume_thread, NULL, resume_thread_func, NULL);

	pthread_join(suspend_thread, NULL);
    pthread_join(resume_thread, NULL);

	return 0;
}

void *suspend_thread_func(void *ptr){
    while (1){
		number += 1;
        printf("number %d\n", number);
		if (number==3) {
            printf("Task is suspended\n");
            suspendThread();
            printf("Task is resumed\n");
    	}
		sleep(1);
	}
}

void *resume_thread_func(void *ptr){
    while (1){
		if (number == 3){
            sleep(3);
            resumeThread();
            printf("Hello, world ! Has delay for 3 seconds in resume_thread\n");
        }
        // Wait for 2 seconds which is bigger than 1 second wait in suspend_thread
        // so that number is increased properly
        sleep(2);
    }	
}
