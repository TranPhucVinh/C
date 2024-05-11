#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int buffer = 0;

void *producer(void *arg)
{
    int buffer_size = *((int*) arg);

    for (int i = 0; i < buffer_size; i++) {
        pthread_mutex_lock(&mutex);
        buffer += 1;
        printf("Producer thread has produced: %d\n", buffer);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}

#define BUFFER_SIZE 3

int main(int argc, char *argv[]) {
    int *buffer_size = (int*) malloc (sizeof(int));
    *buffer_size = BUFFER_SIZE;

    pthread_t tid;
    pthread_create(&tid, NULL, producer, buffer_size);

    int consumer_consumed = 0;        /* Total units so far consumed */
    bool consumed_done = false;

    /* Use a polling loop to check for available inside the buffer */
    while (1) {
        pthread_mutex_lock(&mutex);
        while (buffer > 0) {             /* Consume all available units */
            consumer_consumed += 1;
            buffer -= 1;
            printf("Main thread has consumed: %d\n", consumer_consumed);

            consumed_done = consumer_consumed >= *buffer_size;
        }
        pthread_mutex_unlock(&mutex);
        
        if (consumed_done) break;
    }

    exit(0);
}
