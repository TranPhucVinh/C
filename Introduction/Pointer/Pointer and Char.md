### char[]

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     
#include <stdint.h>

int main (){
  char hello[] = "hello world"; //hello is an array - pointer
  char *returnChar = hello; //returnChar must be a pointer

  printf("hello[0]: %c \n", hello[0]);
  printf("returnChar[0]: %c \n", returnChar[0]);
  printf("returnChar: %p \n", returnChar);
}
```

```
hello[0]: h
returnChar[0]: h
returnChar: 0x62FE30
```
