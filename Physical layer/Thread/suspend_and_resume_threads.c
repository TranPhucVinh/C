#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *suspend_thread_func(void *ptr);
void *resume_thread_func(void *ptr);

int number;
int suspendFlag = 0;
int suspend_thread_return, resume_thread_return;

pthread_t suspend_thread, resume_thread;
pthread_mutex_t suspendMutex;
pthread_cond_t resumeCond;

void suspendThread()
{
    if(!pthread_mutex_lock(&suspendMutex)){
        pthread_cond_wait(&resumeCond, &suspendMutex);
        pthread_mutex_unlock(&suspendMutex);
    }
}

void resumeThread()
{ 
    if(!pthread_mutex_lock(&suspendMutex)){
        pthread_cond_broadcast(&resumeCond);
        pthread_mutex_unlock(&suspendMutex);
    }
}

int main(void){
    pthread_mutex_init(&suspendMutex, NULL);
    pthread_cond_init(&resumeCond, NULL);
	
	suspend_thread_return = pthread_create(&suspend_thread, NULL, suspend_thread_func, NULL);
    resume_thread_return = pthread_create(&resume_thread, NULL, resume_thread_func, NULL);

	pthread_join(suspend_thread, NULL);
    pthread_join(resume_thread, NULL);

    pthread_mutex_destroy(&suspendMutex);
    pthread_cond_destroy(&resumeCond);

	return 0;
}

void *suspend_thread_func(void *ptr){
    char str[50];
    char suspend[] = "Task is suspended\n", resume[] = "Task is resumed\n";
    while (1){
        memset(str, 0, sizeof(str));
		number += 1;
        sprintf(str, "number %d\n", number);
        write(STDOUT_FILENO, str, sizeof(str));
		if (number==3) {
            write(STDOUT_FILENO, suspend, sizeof(suspend));
            suspendThread();
            write(STDOUT_FILENO, resume, sizeof(resume));
    	}
		sleep(1);
	}
}

void *resume_thread_func(void *ptr){
    char str[] = "Has delay for 3 seconds in resume_thread\n";
    while (1){
		if (number == 3){
            sleep(3);
            resumeThread();
            write(STDOUT_FILENO, str, sizeof(str));
        }
        sleep(1);
    }	
}
