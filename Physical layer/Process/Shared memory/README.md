Shared memory allows 2 or more process to share the same region of physical memory. When one process copies the data into a shared memory, that data is immediately available to all other process sharing the same segment. That's why shared memory is **the fastest IPC**.

# API

## shmget()

Allocates a System V shared memory segment

```c
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```

``shmget()`` returns the identifier of the System V shared memory segment associated with the value of the argument ``key``.  A new shared memory segment, with size equal to the value of ``size`` rounded up to a multiple of ``PAGE_SIZE``.

* ``IPC_CREAT``: Create a new segment
* ``IPC_EXCL``: This flag is used with ``IPC_CREAT`` to ensure that this call creates the segment. If the segment already exists, the call fails.

**Return**: On success, a valid shared memory identifier is returned. On error, ``-1`` is returned, and ``errno`` is set to indicate the error.

## shmat()

```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

``shmat()`` attaches  the System V shared memory segment identified by shmid to the address space of the calling process.  The attaching address is specified by shmaddr with one of the following criteria:

*  If ``shmaddr`` is ``NULL``, the system chooses a suitable (unused) address at which to attach the segment.

``shmflg``:

* ``SHM_EXEC``: Allow the contents of the segment to be executed. The caller must have execute permission on the segment.
* ``SHM_RDONLY``: Attach the segment for read-only access. The process must have read permission for the segment.

**Return**: On success, the address of the attached shared memory segment is returned; on error, ``(void *) -1`` is returned, and ``errno`` is set to indicate the cause of the error.

## shmdt()

```c
int shmdt(const void *shmaddr);
```

Detaches the shared memory segment located at the address specified by shmaddr from the address space of the calling process. The to-be-detached segment must be currently attached with shmaddr equal to the value returned by the attaching ``shmat()`` call. After detaching, the previously shared memory segment is unable to access and causes **Segmentation fault** when trying to read it. 

**Note**: This function does not delete the shared memory segment.

```c
// This program causes Segmentation fault
#define SHM_KEY 1
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL

int id;
int *ptr;
id = shmget(SHM_KEY, SIZE, IPC_CREAT|IPC_EXCL|0777);
if (id > -1) printf("Shared memory segment with ID %d is created successfully\n", id);
else {
    printf("Unable to create shared memory segment share memory key %d\n", SHM_KEY);
    return 0;
}
ptr = shmat(id, SHM_ADDR, SHM_EXEC);
if (*ptr == -1) printf("Shared memory segment is unable to be attached\n");
else printf("Shared memory segment is attached successfully\n");
*ptr = 1234;

printf("Before detaching, shared memory segment with address %x has value %d\n", ptr, *ptr);
if (!shmdt(ptr)) printf("Shared memory segment is detached successfully\n");
else printf("Unable to detached shared memory segment\n");

printf("after detaching %d\n", *ptr); // Segmentation fault
```

# Implementations

* [Write and read an int value in a shared memory region]()
* [Write and read int and string value in 2 shared memory regions]()
* [Remove a shared memory region]()