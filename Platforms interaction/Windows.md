# Environment

For GCC build on Windows, install ``TDM-GCC-64``.

To compile a program to run on Windows with ``wine``, use ``winegcc``: ``winegcc test.c``

``a.out.so`` file will be exported.

Then run on wine command prompt: ``wine cmd``

```
Z:\home\tranphucvinh\Documents\Gitlab\windows-batch>a.out.so
```

# Process library in Windows

``process.h`` is a C header file which contains function declarations and macros used in working with threads and processes.
Most C compilers that target DOS, Windows 3.1x, Win32, OS/2, Novell NetWare or DOS extenders supply this header and the library functions in their C library. 

Neither the header file nor most of the functions are defined by either the ANSI/ISO C standard or by POSIX.

If you are on Linux or compile with c99/ansi standard, ``process.h`` will not be available. ``process.h`` supports the spawn functions which are similar to ``fork()`` in Unix. ``fork()`` are not available in ``process.h``

# TCP socket

For TCP socket on Windows, use library  ``Winsock 2`` (``winsock2.h``) which is built-in in GCC compiler.

``winegcc`` doesn't support ``winsock2.h``

# System time

Print out a string after every one second with library ``time.h``.

```c
#include <stdio.h> 
#include <time.h> 

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    clock_t start_time = clock(); // Storing start time 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 		; 
} 
  
// Driver code to test above function 
int main(){ 
    while (1){
		printf("Hello, World \n");
		delay(1);
	}
} 
```
