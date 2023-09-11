#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define PSHARED 0
#define SEM_VAL	1

sem_t mutex;
char displayed_string[30];

void *func_thread_1(void *ptr);
void *func_thread_2(void *ptr);

pthread_t thread_1;
pthread_t thread_2;

char thread_1_str[] = "Thread 1\n";
char thread_2_str[] = "Thread 2\n";

int main()
{
	sem_init(&mutex, PSHARED, SEM_VAL);
	pthread_create(&thread_1, NULL, func_thread_1, NULL);
	pthread_create(&thread_2, NULL, func_thread_2, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	sem_destroy(&mutex);
}

void *func_thread_1(void *ptr){
	write(STDOUT_FILENO, thread_1_str, sizeof(thread_1_str));

	if (!sem_wait(&mutex)){
		memcpy(displayed_string, "Hello, World !\n", 15);
		sem_post(&mutex);
	}
}

void *func_thread_2(void *ptr){
	if (!sem_wait(&mutex)){
		write(STDOUT_FILENO, displayed_string, sizeof(displayed_string));
		sem_post(&mutex);
	}
	write(STDOUT_FILENO, thread_2_str, sizeof(thread_1_str));
}