### Introduction 

````c
#define PRINT_HELLO_WORLD printf("Hello world")
#define PI 3.14159
#define a 6
#define PIN_SPI_SS    (10)

main(){
	printf("%d \n", a);
	printf("%f \n", PI);
	PRINT_HELLO_WORLD;
	printf("%d \n", PIN_SPI_SS);
}	
````
**Result**
```
6
3.14159
Hello world
10
```

### Macro with arguments

```c
#define defineFunction(a) a+1

main(){
	int  result = defineFunction(6);
	printf("%d \n", result); //7
}	
```

```c
#define defineFunction(returnValue) returnValue+1

int a;

main(){
	printf("%d \n", defineFunction(a=14)); //15
}
```

### Redefine macro variable

**head.h**

```c
#define integerValue 190
```

**main.c**

```c
#include <stdio.h>
#include "head.h"

int main (){
  printf("%d \n", integerValue);
  #undef integeValue
  #define integerValue 100
  printf("%d \n", integerValue);
}
```

**Result**

```
190
100
```

### Predefine during compilation

```c
#include <stdio.h>

//Variable name is not define
main(){
	printf("name: %d \n", name);
}	
```

Predefine during compilation: ``gcc -D name=12 test.c``

Result: ``name: 12``

**Proper macro predefine with ``#ifndef``**

```c
#include <stdio.h>

#ifndef name
#define name 4
#endif

main(){
	printf("name: %d \n", name);
}	
```

Compile ``gcc -D name=12 test.c``

Result: ``name: 12``