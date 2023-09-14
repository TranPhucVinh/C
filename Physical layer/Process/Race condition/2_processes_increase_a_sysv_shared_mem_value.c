#include <stdio.h>
#include <fcntl.h> 
#include <errno.h>
#include <sys/shm.h>
#include <semaphore.h>

#define SHM_KEY 1 // Shared memory SHM_KEY must exist at first
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR    NULL
#define SEM_VAL	    1

#define RANGE   1000000
// #define RANGE   5 // Small RANGE value like this won't cause race condition

#define SEM_NAME    "/SEMAPHORE_SHARED_MEM"
#define PSHARED     1

int id;
int *ptr;
sem_t *mutex;
int main(){
    id = shmget(SHM_KEY, SIZE, 0777);
    ptr = shmat(id, SHM_ADDR, SHM_EXEC);

    mutex = sem_open(SEM_NAME, O_RDWR);

    if (mutex == SEM_FAILED) {
        printf("Fail open %s\n", SEM_NAME);
        printf("errno %d\n", errno);
        if (errno = 13) printf("Permission denied\n");
    }
    else printf("Open %s successfully\n", SEM_NAME);

    for (int i = 0; i < RANGE; i++){
        if (!sem_wait(mutex)){
            *ptr += 1;
            sem_post(mutex);
        } else printf("%d fails to lock\n", *ptr);
    }
    
    printf("%d\n", *ptr);
}
