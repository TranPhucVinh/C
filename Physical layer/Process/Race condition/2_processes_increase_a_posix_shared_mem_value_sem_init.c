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
#define BASE_ADDR   0   //No specific base address to set in shared memory

#define SHARED_MEM_PATH    "/dev/shm/SHARED_MEMORY" //POSIX shared memory path
#define SHM_NAME    "/SHARED_MEMORY"
#define SEM_NAME    "/SEMAPHORE_SHARED_MEM"

#define DUMMY_PROJECT_ID   1

//sem_init() macro
#define PROCESS_SHARED      1 // Greater than 0 value as flag for sem_init() to share the unnamed semaphore between processes
#define SEMAPHORE_VAL      1 // Semaphore init value

int id;
int *ptr;
sem_t   *sem_ptr;

long round_up(long n, long mult);

int main(){
    long pagesize;
    long semsize;

    pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize == -1) {
        perror("sysconf(_SC_PAGESIZE)");
        return 1;
    }

    int shm_fd = shm_open(SHM_NAME, O_CREAT|O_RDWR, 0777);
    if (shm_fd > 0) printf("Shared memory object %s is opened successfully with fd %d\n", SHM_NAME, shm_fd);
    else printf("Unable to open %s\n", SHM_NAME);

    semsize = round_up(sizeof(sem_t), pagesize);
    if (ftruncate(shm_fd, semsize) == -1) {
        perror("ftruncate");
        return 1;
    }

    sem_ptr = mmap(NULL, semsize, PROT_WRITE, MAP_SHARED, shm_fd, BASE_ADDR);
    if (sem_ptr < 0){
        printf("mmap() for semaphore fails\n");
        return 0;
    }

    if (sem_init(sem_ptr, PROCESS_SHARED, SEMAPHORE_VAL) == -1 ){
        printf("Unable to init unnamed POSIX semaphore\n");
        return 0;
    }
    printf("Init unnamed POSIX semaphore successfully\n");

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

    #define RANGE 1000000
    for (int i = 0; i < RANGE; i++) {
        if(!sem_wait(sem_ptr)) {
            *ptr += 1;
            sem_post(sem_ptr);
        } else printf("fail to lock\n");
    }
    printf("%d\n", *ptr);

    if (shmdt(ptr) < 0) {
        printf("detach share mem fail: %d\n", errno);
    }
}

long round_up(long n, long mult)
{
    return ((n + mult - 1) / mult) * mult;
}
