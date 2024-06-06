# [Function](#function)
## C doesn't support function overloading

C doesn't support function overloading as it is not an OOP language

For function overloading in [CPP](https://github.com/TranPhucVinh/Cplusplus), check [CPP function overloading document](https://github.com/TranPhucVinh/Cplusplus/tree/master/Introduction/Function#function-overloading).

## C doesn't support default arguments

Only CPP supports default arguments, check [CPP function for this implementation](https://github.com/TranPhucVinh/Cplusplus/tree/master/Introduction/Function#default-arguments).
# [Variable](Variable.md)
# [Header](https://github.com/TranPhucVinh/C/tree/master/Introduction/Header)
# [Macro](https://github.com/TranPhucVinh/C/tree/master/Introduction/Macro)
# [Data type](https://github.com/TranPhucVinh/C/tree/master/Introduction/Data%20type)
# [Keywords](https://github.com/TranPhucVinh/C/tree/master/Introduction/Keywords)
# [Linkage](Linkage.md)

# Error handling

C doesn't support exception handling, ``try catch`` and ``throw`` are not available in C with GCC.

Error can be checked with ``errno`` of library ``errno.h``

```c
#include <errno.h>
int fileDescription = open(filePath, O_RDONLY);
printf("%d\n", errno);
```

If the file is exist and no error happen, ``errno`` is ``0``.

If the file is not exist, ``errno`` will be ``2`` (``ENOENT``).

``errno`` command, which is a part of moreutils package, can be used to lookup the error number value and its name. ``errno`` is mapped to ``errno.h``.

Install: ``sudo apt install moreutils``

E.g:

```sh
username$hostname: errno 2
```

```
ENOENT 2 No such file or directory
```

```sh
username$hostname: errno EBUSY
```

```
EBUSY 16 Device or resource busy
```

## EBUSY

Trying to open a file 2 times and EBUSY error doesn't happen

```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()
#include <errno.h>

#define FILE "evk_test.c"

int fd;

int main(){
    fd = open(FILE, O_RDWR);
    if (fd > 0) {
        open(FILE, O_RDWR);
        perror("DEBUG");
        printf("Error number: %d\n", errno);
        close(fd);
    } else printf("Error\n");
}
```

``EBUSY`` still doesn't happen if using the source code above with device file like ``/dev/tty``.

The device file can't handle **EBUSY** by itself if the error handler are not implemented in its source code. To handle any specific errno, like **EBUSY** on character device, that device must handle this error in its operation, [like the open operation](https://github.com/TranPhucVinh/C/blob/master/Kernel/Character%20device/Create%20character%20device/README.md#handle-specific-error-from-errno-from-userspace).

## EFAULT

``EFAULT`` is bad address issue and must be return when ``copy_from_user()`` fail. Check [the example in character device to trigger this error](https://github.com/TranPhucVinh/C/blob/master/Kernel/Character%20device/README.md#operation-with-character-device-by-ioctl).

## strerror()

```c
char *strerror(int errnum);
```

``strerror()`` returns a string that describes the error code passed in the argument ``errnum``.

```c
#include <errno.h>

int main(){
    int fileDescription = open("file_not_existed.md", O_RDONLY);
    printf("Error %d: %s\n", errno, strerror(errno));
    return 0;
}
```
**Result**: ``Error 2: No such file or directory``

# Get libc version

```c
#include <gnu/libc-version.h>
printf("%s\n", gnu_get_libc_version());
```
# [Unity unit test framework](Unit%20test.md)
## Stub function

A **stub** is a dummy or a testable replacement for a function or a variable.

**How to stub a function**: If there is a call to a function that handles a hardware functionality (for example a function to read temperature from a sensor), but this function is not testable in an offline environment like a standalone computer or in your local compiler, then you **STUB** it (or **REPLACE** it) with a dummy function, that does nothing or just increments a dummy variable, like ``x``.

So after you run you code, if you find that the variable ``x`` has been incremented, you know that the function (temperature sensor function) has been called.

For example, the temperature sensor function is ``Read_TempSens()``. We stub it with a dummy variable ``Test_ReadTemp`` as shown below

```c
int Test_ReadTemp;
#undef Read_TempSens()
#define Read_TempSens() Test_ReadTemp++
```
# Comparison to OOP

There are several cases where OOP with CPP must be implemented when comparing to their corresponding ones in C:

* [Stack building](../Data%20structure/Stack/README.md#build%20stack%20with%20array%20using%20struct)
* [Suspend and resume thread](../Physical%20layer/Thread/README.md#inter-task-communication)
