# Environment

For GCC build on Windows, install ``TDM-GCC-64``.

To compile a program to run on Windows with ``wine``, use ``winegcc``: ``winegcc test.c``

``a.out.so`` file will be exported.

Then run on wine command prompt: ``wine cmd``

```
Z:\home\tranphucvinh\Documents\Gitlab\windows-batch>a.out.so
```
# File IO systemcall

File IO systemcall API in ``unistd.h`` and ``fcntl.h`` work properly in Windows:
```c
// This read file program works properly in Windows
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()

int fd;

int main(){
    char buffer[10];

    fd = open("README.md", O_RDONLY);
    if (fd > 0){
        read(fd, buffer, 10);
        puts(buffer);
    }
}
```
# Process library in Windows

``process.h`` is a C header file which contains function declarations and macros used in working with threads and processes.
Most C compilers that target DOS, Windows 3.1x, Win32, OS/2, Novell NetWare or DOS extenders supply this header and the library functions in their C library. 

Neither the header file nor most of the functions are defined by either the ANSI/ISO C standard or by POSIX.

If you are on Linux or compile with c99/ansi standard, ``process.h`` will not be available. ``process.h`` supports the spawn functions which are similar to ``fork()`` in Unix. ``fork()`` are not available in ``process.h``

# TCP socket

TCP Unix functions are not supported on Windows. For TCP socket on Windows, use library  ``Winsock 2`` (``winsock2.h``) which is built-in in GCC compiler.

``winegcc`` doesn't support ``winsock2.h``

# System time

``time.h`` and ``sys/time.h`` are available with GCC on Windows, check the [corresponding example in Physical layer/Time](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Time/Examples.md) for implementation with functions from those library, e.g **Delay for a number of seconds with sys.time.h**.
