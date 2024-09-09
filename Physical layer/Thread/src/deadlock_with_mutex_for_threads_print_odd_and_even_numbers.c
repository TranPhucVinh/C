#include <stdio.h>
#include <pthread.h>

#define NUMBER  7

void *odd_number(void *ptr);
void *even_number(void *ptr);

int number = NUMBER;

pthread_mutex_t lock;

int main() {
    pthread_mutex_init(&lock, NULL);

    pthread_t thread_odd, thread_even;
    int thread_odd_return, thread_even_return;

    thread_odd_return = pthread_create(&thread_odd, NULL, odd_number, &number);
    thread_even_return = pthread_create(&thread_even, NULL, even_number, &number);

    pthread_join(thread_odd, NULL);
    pthread_join(thread_even, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}

void *odd_number(void *ptr) {
    if(!pthread_mutex_lock(&lock)){
        if ( *(int*)ptr > 0) {
            printf("Odd number: %d\n", *(int*)ptr);

            *(int*)ptr -= 1;
            pthread_mutex_unlock(&lock);
            even_number(ptr);           
		} else {
            pthread_mutex_unlock(&lock);
        }

    } else printf("Fail to lock mutex\n");
}

void *even_number(void *ptr) {
    if(!pthread_mutex_lock(&lock)){
        if ( *(int*)ptr > 0) {
            printf("Even number: %d\n", *(int*)ptr);
            
            *(int*)ptr -= 1;
            pthread_mutex_unlock(&lock);
            odd_number(ptr);
        } else {
            pthread_mutex_unlock(&lock);// With recursive mutex, it must be unlocked after using the shared resource 
        }
    } else printf("Fail to lock mutex\n");
}
