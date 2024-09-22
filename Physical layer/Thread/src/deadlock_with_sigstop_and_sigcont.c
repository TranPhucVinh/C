#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

void *suspend_thread_func(void *ptr);
void *resume_thread_func(void *ptr);

int number = 0;

pthread_t suspend_thread, resume_thread;

int main(){
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

            // This will suspend the whole process, not this signal process.
            // This causes deadlock as the whole is suspended infinitely by this thread.
            pthread_kill(suspend_thread, SIGSTOP);
            printf("Task is resumed\n");
    	}
		sleep(1);
	}
}

void *resume_thread_func(void *ptr){
    while (1){
		if (number == 3){
            sleep(3);
            pthread_kill(suspend_thread, SIGCONT);
            printf("Hello, world ! Has delay for 3 seconds in resume_thread\n");
        }
        sleep(2);
    }	
}
