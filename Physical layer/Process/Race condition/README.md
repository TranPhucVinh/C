# Two processes increase the value of a shared memory region

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
**Result** ``540637 1183649`` (Expected ``1000000 2000000`` 
