### char[]

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     
#include <stdint.h>

int main (){
  char hello[] = "hello world"; //hello is an array - pointer
  char *returnChar = hello; //returnChar must be a pointer

  printf("hello[0]: %c \n", hello[0]); //hello[0]: h
  printf("returnChar[0]: %c \n", returnChar[0]); //returnChar[0]: h
  printf("returnChar: %p \n", returnChar); //returnChar: 0x62FE30
}
```