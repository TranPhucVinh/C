The ‘#pragma’ directive is the method specified by the C standard for providing additional information to the compiler, beyond what is conveyed in the language itself. ``#pragma`` varies between compilers. Those are GCC defined ``#pragma``

# #pragma GCC dependency

**#pragma GCC dependency** allows you to check the relative dates of the current file and the dependent files. If the dependent file is more recent than the current file, a warning is issued.
```
working_folder
|--head.h
|--head.c
|--main.c
```
```c
#include "head.h"

#pragma GCC dependency "head.c"
int main() {}
```
**Result**: If ``head.c`` is newer then ``main.c`` then:
```
$ gcc main.c
main.c:3:24: warning: current file is older than head.c
 #pragma GCC dependency "head.c"
                        ^
```
# #pragma GCC poison

**#pragma GCC poison** to avoid completely calling some identifiers, i,e functions, variables, in your program. Calling them then will result in compilation error.

```c
#include "head.h"

#pragma GCC poison printf add number

int add(int a, int b){
	return a+b;
}
int number = 123;
int main(){
	printf("Hello, World !\n");
}
```
**Result**
```
main.c:5:5: error: attempt to use poisoned "add"
 int add(int a, int b){
     ^
main.c:8:5: error: attempt to use poisoned "number"
 int number = 123;
     ^
main.c: In function 'main':
main.c:10:2: error: attempt to use poisoned "printf"
  printf("Hello, World !\n");
  ^
```
# #pragma GCC warning and #pragma GCC error
**#pragma GCC warning** gives message warning when compile the program
```c
int main(){
	#pragma GCC warning "Hello, World !"
}
```
**Result**
```
$gcc main.c
main.c: In function 'main':
main.c:11:22: warning: Hello, World !
  #pragma GCC warning "Hello, World !"
```
**#pragma GCC error** gives compilation error
```c
int main(){
	#pragma GCC error "Hello, World !"
}
```
**Result**: This gives compilation error
```
$gcc main.c
main.c: In function 'main':
main.c:11:22: warning: Hello, World !
  #pragma GCC warning "Hello, World !"
```

# #error

Like **#pragma GCC error**, **#error** is used to give compilation error
```c
#include <stdio.h>

int main(){
	#error POWER is not defined or is less than 2
}
```
It's better to use **#error** along with macro **#if #endif**
