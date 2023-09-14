#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>  
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE    100// Size of the share memory segment

#define SHM_ADDR         NULL
#define SHARED_MEM_PATH    "/dev/shm/SHARED_MEMORY" //POSIX shared memory path
#define SEM_NAME    "/SEMAPHORE_SHARED_MEM"

#define DUMMY_PROJECT_ID   1

int id;
int *ptr;
sem_t *sem;

int main(){
    sem = sem_open(SEM_NAME, O_RDWR, 777, 1);
    if (sem == SEM_FAILED) {
        printf("Fail to open %s\n", SEM_NAME);
        printf("errno %d\n", errno);
        if (errno == 13) printf("Permission denied\n");
        return 0;
    }
    else printf("Open %s successfully\n", SEM_NAME);

    key_t shm_key = ftok(SHARED_MEM_PATH, DUMMY_PROJECT_ID);

    if (shm_key == -1) {
        printf("error ftok the shared mem: %d\n", errno);
        return 0;
    }
    printf("ftok() success\n");
    id = shmget(shm_key, SIZE, 0777|IPC_CREAT);
    if (id > -1) printf("Shared memory segment from shm_key %d with ID %d is got successfully\n", shm_key, id);
    else {
        printf("Unable to get shared memory segment share memory key %d\n", id);
        printf("errno %d\n", errno);
        return 0;
    }

    ptr = shmat(id, SHM_ADDR, SHM_EXEC|0777);

    if (*ptr == -1) printf("Shared memory segment is unable to be attached\n");
    else {
        printf("Shared memory segment is attached successfully with value %d\n", *ptr);
    }

    if(!sem_wait(sem)) {
        sem_post(sem);
    }

    sleep(1);

    #define RANGE 1000000
    for (int i = 0; i < RANGE; i++) {
        if(!sem_wait(sem)) {
            *ptr += 1;
            sem_post(sem);
        } else printf("fail to lock\n");
    }
    printf("fail %d\n", *ptr);

    if (shmdt(ptr) < 0) {
        printf("detach share mem fail: %d\n", errno);
    }

}
