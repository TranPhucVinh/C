# Two processes increase the value of a System V shared memory region

Start 2 process which increases the value of a shared memory region. By using a shell script to start them in order to cause race condition, run those processes as background.

``increase_shared_mem_value.c``
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHM_KEY 1 // Shared memory SHM_KEY must exist at first
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL

#define RANGE   1000000
// #define RANGE   5 // Small RANGE value like this won't cause race condition

int id;
int *ptr;

int main(){
    id = shmget(SHM_KEY, SIZE, 0777);
    ptr = shmat(id, SHM_ADDR, SHM_EXEC);

    // This will increase 
    for (int i = 0; i < RANGE; i++){
        *ptr += 1;
    }
    printf("%d ", *ptr);
}
```
``race_condition.sh``: Run this script to build increase_shared_mem_value.c then start 2 processes in the background.
```sh
gcc increase_shared_mem_value.c

# Run 2 a.out as background process to have race condition
./a.out&
./a.out&

# Running 2 a.out as foreground process won't trigger race condition
# ./a.out
# ./a.out
```
**Result** ``540637 1183649`` (Expected ``(don't care 1st a.out&) 2000000 (2nd a.out& must be 2000000)`` 

**Problem solved**: Program [2_processes_increase_a_sysv_shared_mem_value.c](2_processes_increase_a_sysv_shared_mem_value.c) with a POSIX named semaphore previously created by [sem_open()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Semaphore.md#sem_open).

For this System V race condition, espeically with shmget() which takes an existed SHM_KEY, using [sem_open()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Semaphore.md#sem_open) to solve the race condition is the best solution. Using unamed semaphore [sem_init()]() doesn't work as its memory mapping to share the unamed semaphore between the processes require the file descriptor from the share memory reqgion which doesn't exist in the System V shared memory API. Reference to the [sem_init implementation to solve the same race condition issue in POSIX shared memory]().
# Two processes increase the value of a POSIX shared memory region
``write_posix_shared_mem.c``
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>  
#include <errno.h>

#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL
#define SHARED_MEM_PATH    "/dev/shm/SHARED_MEMORY" //POSIX shared memory path
#define DUMMY_PROJECT_ID   1

int id;
int *ptr;

int main(){
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
        *ptr += 1;
    }
    printf("%d\n", *ptr);

    shmdt(ptr);
}
```
Script to run:
```sh
set -e #Quit script if any command, like gcc write_shared_mem.c, fails
./remove_posix_shared_mem 
./create_posix_shared_mem  
gcc write_posix_shared_mem.c -o write_posix_shared_mem -lrt
./write_posix_shared_mem & # Run write_shared_mem as background job
./write_posix_shared_mem & # Run write_shared_mem as background job
```
**Result**
```sh
806297
1049490 //Expected 2000000
```
To solve that race condition, we can use an existed POSIX semaphore to manage the shared memory value between the 2 background job ``write_shared_mem``.

**Problem solved**: 

* Program [2_processes_increase_a_posix_shared_mem_value.c](2_processes_increase_a_posix_shared_mem_value.c) with a **POSIX named semaphore** previously created by [sem_open()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Semaphore.md#sem_open) (named semaphore).
* Program [2_processes_increase_a_posix_shared_mem_value_sem_init.c](2_processes_increase_a_posix_shared_mem_value.c) with a **POSIX unnamed semaphore** created by [sem_init()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Semaphore.md#sem_open) along with the memory sharing/trauncating process achieved by [mmap()]().
