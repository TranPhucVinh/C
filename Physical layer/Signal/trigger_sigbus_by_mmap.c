#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/shm.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>   

#define SHM_NAME    "/SHARED_MEMORY"
#define BASE_ADDR   0   //No specific base address to set in shared memory

int     *ptr;
sem_t   *sem_ptr;

void signal_handler(int signal_number);

int main(){
    signal(SIGBUS, signal_handler);
    int shm_fd = shm_open(SHM_NAME, O_CREAT|O_RDWR, 0777);
    if (shm_fd < 0) {
		printf("Unable to open %s\n", SHM_NAME);
		return 0;
	}
	printf("Shared memory object %s is opened successfully with fd %d\n", SHM_NAME, shm_fd);

    sem_ptr = mmap(NULL, sizeof(sem_t), PROT_WRITE, MAP_SHARED, shm_fd, BASE_ADDR);
    if (sem_ptr < 0){
        printf("mmap() for semaphore fails\n");
        return 0;
    }
	printf("Semaphore mmap() successfully\n");

	// This sem_init() triggers SIGBUS
    if (sem_init(sem_ptr, 1, 1) == -1 ){
        printf("Unable to init POSIX semaphore\n");
        return 0;
    }
    printf("Init POSIX semaphore successfully\n");
}

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "SIGBUS: Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}
