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

# Windows signal

Signal in Windows Git Bash

```
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGEMT       8) SIGFPE       9) SIGKILL     10) SIGBUS
11) SIGSEGV     12) SIGSYS      13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGURG      17) SIGSTOP     18) SIGTSTP     19) SIGCONT     20) SIGCHLD
21) SIGTTIN     22) SIGTTOU     23) SIGIO       24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGPWR      30) SIGUSR1
31) SIGUSR2     32) SIGRTMIN    33) SIGRTMIN+1  34) SIGRTMIN+2  35) SIGRTMIN+3
36) SIGRTMIN+4  37) SIGRTMIN+5  38) SIGRTMIN+6  39) SIGRTMIN+7  40) SIGRTMIN+8
41) SIGRTMIN+9  42) SIGRTMIN+10 43) SIGRTMIN+11 44) SIGRTMIN+12 45) SIGRTMIN+13
46) SIGRTMIN+14 47) SIGRTMIN+15 48) SIGRTMIN+16 49) SIGRTMAX-15 50) SIGRTMAX-14
51) SIGRTMAX-13 52) SIGRTMAX-12 53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9
56) SIGRTMAX-8  57) SIGRTMAX-7  58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4
61) SIGRTMAX-3  62) SIGRTMAX-2  63) SIGRTMAX-1  64) SIGRTMAX
```

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
