Use ``sanitizers`` (built-in ``GCC`` and ``G++``) to detect memory leak

## GCC

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char *str;

   str = (char *) malloc(100 * sizeof(char));
   strcpy(str, "Learn malloc");
}   
```

Compile: ``gcc test.c -fsanitize=leak``, then run ``./a.out``, there will be error:

```
=================================================================
==27291==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 100 byte(s) in 1 object(s) allocated from:
    #0 0x7fc3e886f795 in __interceptor_malloc (/usr/lib/x86_64-linux-gnu/liblsan.so.0+0xc795)
    #1 0x400697 in main (/home/tranphucvinh/Documents/Gitlab/windows-batch/a.out+0x400697)
    #2 0x7fc3e84b983f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

SUMMARY: LeakSanitizer: 100 byte(s) leaked in 1 allocation(s).
```

If adding ``printf()``, the memory leak error above won't happen:

```c
int main () {
   char *str;

   str = (char *) malloc(100 * sizeof(char));
   strcpy(str, "Learn malloc");
   printf("String: %s \n", str); //Learn malloc
}   
```
## G++

```c
#include <stdio.h>

int main(){
   int *int_number = new int;
	int *int_array = new int[2];
	*int_number = 12;
	int_array[0] = 1;
	int_array[1] = 2;
	printf("int_number: %d\n", *int_number); //12
	printf("int_array[1]: %d\n", int_array[1]); //2
}
```

Compile: ``g++ test.cpp -fsanitize=leak``, then run ``./a.out``, there will be error:

```c
int_number: 12
int_array[1]: 2

=================================================================
==27844==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 8 byte(s) in 1 object(s) allocated from:
    #0 0x7f49ff30b975 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/liblsan.so.0+0xd975)
    #1 0x400735 in main (/home/tranphucvinh/Documents/Gitlab/windows-batch/a.out+0x400735)
    #2 0x7f49fef5483f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0x7f49ff30b815 in operator new(unsigned long) (/usr/lib/x86_64-linux-gnu/liblsan.so.0+0xd815)
    #1 0x400727 in main (/home/tranphucvinh/Documents/Gitlab/windows-batch/a.out+0x400727)
    #2 0x7f49fef5483f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

SUMMARY: LeakSanitizer: 12 byte(s) leaked in 2 allocation(s).
```