## mmap()

```c
#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```

``mmap()``: creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is specified in ``addr``.  The length argument specifies the length of the mapping (which must be greater than 0).

If ``addr`` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.

The contents of a file mapping, are initialized using length bytes starting at ``offset``.

On success, ``mmap()`` returns a pointer to the mapped area.

``prot``: memory protection of the mapping (and must not conflict with the open mode of the file).

*  ``PROT_EXEC``: Pages may be executed.
* ``PROT_READ``: Pages may be read.
* ``PROT_WRITE``: Pages may be written.
* ``PROT_NONE``: Pages may not be accessed.

``flags``:

* ``MAP_SHARED``: Share memory
* ``MAP_ANONYMOUS``: The mapping doesn't involve any file descriptor (i.e fd=-1)

### Examples

**Example 1**: [Control GPIO of Raspberry Pi by direct memory access using mmap()](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Physical%20layer/GPIO/direct_register_access_control_gpio.c), notice that ``addr`` param in ``mmap()`` is ``NULL`` in this case.

**Example 2**: Use ``mmap()`` to read content of a file

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
    int fd = open("evk_test.c", O_RDONLY);

    /*
        Get page size of fd to read size of the file then send as page size argument 
        of fstat()
    */
    if (fstat(fd, &sb) == -1) printf("Couldn't get file size\n");
    else printf("File size %ld\n", sb.st_size);

    //MAP_PRIVATE: Use map private to make the reading private, using other map value is fine
    char *file_content = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, BASE_ADDR);

    printf("%s\n", file_content);
    close(fd);
    munmap(file_content, sb.st_size);//Unmap file to save memory
    return 0;
}
```
