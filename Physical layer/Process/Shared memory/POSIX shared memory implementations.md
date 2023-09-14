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
