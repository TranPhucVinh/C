#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *display_string(void *ptr){
	while (1){
        printf("%s\n", (char*)ptr);
        sleep(1);
    }
}

void *display_int(void *ptr){
	while (1){
        printf("%d\n", *((int*)ptr));
        sleep(1);
    }
}

int main()
{  
	pthread_t str_thread, int_thread;
    int number = 56;
    char str[] = "Hello, World !";
    pthread_create(&str_thread, NULL, display_string, str);
    pthread_join(int_thread, NULL);
	pthread_create(&int_thread, NULL, display_int, &number);
	pthread_join(str_thread, NULL);
}