Print out the enter value

```c
#include <stdio.h>

int a;

int main(){
   while(1){
      scanf("%d", &a);
      printf("%d \n", a);
   }
}
```

Enter a string with ``scanf()``

```c
#include <stdio.h>

char enteredString[100];

int main(){
   while(1){
      scanf("%s", enteredString);
      printf("Entered string: %s \n", enteredString);
   }
}
```

```
Hello, World!
Entered string: Hello, 
Entered string: World! 
```

Using ``scanf()`` is not highly recommended as it doesn't have buffer overflow protection, unless you know for certain that the input will always be of a specific format (and perhaps not even then).


A proper word entering can be solved with ``fgets()``

```c
#include <stdio.h>

char enteredString[100];

int main(){
   while(1){
      fgets(enteredString, 100, stdin);
      printf("Entered string: %s", enteredString);
   }
}
```