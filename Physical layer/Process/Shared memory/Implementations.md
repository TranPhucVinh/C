# Write and read an int value in a shared memory region

## Write an int value in a shared memory region

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

// As default share memory key are all 0, so the SHM_KEY shouldn't be 0 to avoid conflict
#define SHM_KEY 1
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL

int id;
int *ptr;
int main(){
    /*
        Flags:
        IPC_CREAT: Create a new shared memory region
        IPC_EXCL: Cause failure if a region with SHM_KEY has already existed
        0777: Mode 777
    */
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
}
```

**Result**

```
Shared memory segment with ID 6750220 is get successfully
Shared memory segment is attached successfully and has value 1234
```

Result of ``ipcs``:

```
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
[Other default Shared Memory Segments with key = 0 ]
0x00000001 6750220    tranphucvi 777        50         0                       
[Other default Shared Memory Segments ]

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
```

**Note**

As default share memory key (``key`` in ``ipcs``) are all 0, so the ``SHM_KEY`` shouldn't be ``0`` to avoid conflict.

For flags:

```c
id = shmget(SHM_KEY, SIZE, IPC_CREAT|IPC_EXCL|0777);
```

* ``IPC_CREAT``: Create a new shared memory region
* ``IPC_EXCL``: Cause failure if a region with SHM_KEY has already existed
* ``0777``: Mode 777

## Read the int value from the shared memory region

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHM_KEY 1 
#define SIZE    50// Size of the shared memory segment

#define SHM_ADDR         NULL

int id;
int *ptr;
int main(){
    id = shmget(SHM_KEY, SIZE, 0777);
    if (id > -1) printf("Shared memory segment with ID %d is get successfully\n", id);
    else {
        printf("No shared memory segment with share memory key %d existed\n", SHM_KEY);
        return 0;
    }

    /*
        SHM_RDONLY: As we only read the value from the shared memory region,
        so use SHM_RDONLY flag for read-only
    */
    ptr = shmat(id, SHM_ADDR, SHM_RDONLY);
    if (*ptr == -1) printf("Shared memory segment is unable to be attached\n");
    else printf("Shared memory segment is attached successfully and has value %d\n", *ptr);
}
```