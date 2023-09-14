# General define
```c
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#define SHARED_MEM_NAME    "/SHARED_MEMORY"
```
# Create a POSIX shared memory
```c
int main(){
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT|O_RDWR, 777);
    if (shm_fd < 0) {
        printf("Fail to create %s\n", SHARED_MEM_NAME);
        printf("errno %d\n", errno);
    } else printf("Create %s successfully\n", SHARED_MEM_NAME); 
}
```
Then ``/dev/shm/SHARED_MEMORY`` is available
# Remove a POSIX shared memory
```c
int main(){
    int shm_fd = shm_unlink(SHARED_MEM_NAME);
    if (shm_fd < 0) {
        printf("Fail to create %s\n", SHARED_MEM_NAME);
        printf("errno %d\n", errno);
    } else printf("Create %s successfully\n", SHARED_MEM_NAME); 
}
```

# Write value to the created POSIX shared memory

As POSIX shared memory API only support [shm_open()]() and [shm_unlink()](), System V functions must be used for write operation. [ftok()]() is used to get the key for [shmget()]():

Write value to the System V shared memory after [creating it](#create-a-system-v-shared-memory):
```c
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL
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

    // As using the POSIX segment for the System V shared memory segment, flag IPC_CREAT
    // must be used to create a new POSIX segment for the write operation
    id = shmget(shm_key, SIZE, 0777|IPC_CREAT);
    if (id > -1) printf("Shared memory segment from shm_key %d with ID %d is got successfully\n", shm_key, id);
    else {
        printf("Unable to get shared memory segment share memory key %d\n", id);
        printf("errno %d\n", errno);
        return 0;
    }

    ptr = shmat(id, SHM_ADDR, SHM_EXEC|0777);
    printf("%d\n", *ptr);
    if (*ptr == -1) printf("Shared memory segment is unable to be attached\n");
    else {
        printf("Shared memory segment is attached successfully with value %d\n", *ptr);
    }
    *ptr = 123;
    printf("%d\n", *ptr);

    // POSIX shared memory detach function shmdt() must be
    // used to keep the value written to the shared memory region.
    // Without shmdt(), the written value *ptr will be lost
    shmdt(ptr);
}
```
# Read value from a System V shared memory after writing to it

After [writing to a System V shared memory](#write-value-to-the-created-system-v-shared-memory), read value from it:
```c
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL
#define SHARED_MEM_PATH    "/dev/shm/SHARED_MEMORY" 
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
    printf("%d\n", *ptr);

    shmdt(ptr);
}
```
# Race condition when 2 process write to a POSIX shared memory
# [Changing value inside parent or child process to effect the left one by using shared memory with mmap()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Process%20cloning/Variable%20inside%20forked%20process.md#with-shared-memory-changing-variable-value-in-parentchild-process-wont-effect-the-left-one)

# Use [mmap()](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Shared%20memory#mmap) to read content of a file

```c
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>//For struct stat

#define BASE_ADDR   0   //0 to read the file from the beginning

struct stat sb;

int main(void){
    int fd = open("main.c", O_RDONLY);

    /*
        Get page size of fd to read size of the file then send as page size argument 
        of fstat()
    */
    if (fstat(fd, &sb) == -1) printf("Couldn't get file size\n");
    else printf("File size %ld\n", sb.st_size);

    //MAP_PRIVATE: Create a private copy-on-write mapping
    char *file_content = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, BASE_ADDR);

    printf("%s\n", file_content);
    close(fd);
    munmap(file_content, sb.st_size);//Unmap file to save memory
    return 0;
}
```
