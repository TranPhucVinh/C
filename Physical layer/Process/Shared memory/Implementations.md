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

# Write and read int and string value in 2 shared memory regions

## Write int and string value in 2 shared memory regions

```c
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>

#define INT_SHM_KEY 1
#define STR_SHM_KEY 2
#define SIZE    50// Size of the share memory segment

#define SHM_ADDR         NULL

int  id;
int  *int_ptr;
char *str_ptr;

int main(){
    id = shmget(INT_SHM_KEY, SIZE, IPC_CREAT|IPC_EXCL|0777);
    if (id > -1) printf("Shared memory segment with ID %d is created successfully\n", id);
    else {
        printf("Unable to create shared memory segment share memory key %d\n", INT_SHM_KEY);
        return 0;
    }
    int_ptr = shmat(id, SHM_ADDR, SHM_EXEC);
    if (*int_ptr == -1) {
        printf("Shared memory segment is unable to be attached\n");
        return 0;
    }
    else printf("Shared memory segment is attached successfully\n");
    *int_ptr = 1234;

    id = shmget(STR_SHM_KEY, SIZE, IPC_CREAT|IPC_EXCL|0777);
    if (id > -1) printf("Shared memory segment with ID %d is created successfully\n", id);
    else {
        printf("Unable to create shared memory segment share memory key %d\n", STR_SHM_KEY);
        return 0;
    }
    str_ptr = shmat(id, SHM_ADDR, SHM_EXEC);
    if (*str_ptr == -1) {
        printf("Shared memory segment is unable to be attached\n");
        return 0;
    }
    else printf("Shared memory segment is attached successfully\n");
    strcpy(str_ptr, "Shared memory string");
}
```

## Read both int and string values from the 2 shared memory regions

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

#define INT_SHM_KEY 1
#define STR_SHM_KEY 2
#define SIZE        50// Size of the shared memory segment

#define SHM_ADDR         NULL

int  id;
int  *int_ptr;
char *str_ptr;

int main(){
    id = shmget(INT_SHM_KEY, SIZE, 0777);
    if (id > -1) printf("Shared memory segment with ID %d is get successfully\n", id);
    else {
        printf("No shared memory segment with share memory key %d existed\n", INT_SHM_KEY);
        return 0;
    }

    int_ptr = shmat(id, SHM_ADDR, SHM_RDONLY);
    if (*int_ptr == -1) printf("Shared memory segment is unable to be attached\n");
    else printf("*int_ptr: %d\n", *int_ptr);

    id = shmget(STR_SHM_KEY, SIZE, 0777);
    if (id > -1) printf("Shared memory segment with ID %d is get successfully\n", id);
    else {
        printf("No shared memory segment with share memory key %d existed\n", STR_SHM_KEY);
        return 0;
    }

    str_ptr = shmat(id, SHM_ADDR, SHM_RDONLY);
    if (*str_ptr == -1) printf("Shared memory segment is unable to be attached\n");
    else printf("*str_ptr: %s\n", (char*)str_ptr);
    return 0;
}
```

# Remove a shared memory region

``ipcrm -m shmid``: Remove share memory with ``shmid``. E.g: ``ipcrm -m 6651916``

To remove by ``shmctl()``:

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHM_KEY 1
#define SIZE    50// Size of the shared memory segment

int id;
int main(){
    id = shmget(SHM_KEY, SIZE, 0777);
    if (id > -1) printf("Shared memory segment with ID %d is get successfully\n", id);
    else {
        printf("No shared memory segment with share memory key %d existed\n", SHM_KEY);
        return 0;
    }

    if (!shmctl(id, IPC_RMID, NULL)) printf("Remove shared memory segment with ID %d successfully\n", id);
    else printf("Unable to remove shared memory segment with ID %d\n", id);
}
```