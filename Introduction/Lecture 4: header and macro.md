# Header file

### Basic header file

**head.h**

```c
void helloworld(){
	printf("Hello World");
}

int value = 6;
```

**main.c**

```c
#include <stdio.h>
#include "head.h"

main(){
	helloworld();
	printf("%d \n", value);
}
```

**Result**

```
Hello World
6
```

**Declare variable in header file**

**head.h**

```c
int value;
```

**main.c**

```c
int main (){
	value = 18;
	printf("%d ", value);
}
```

```
18
```

### Error

**header.h**

```c
int a;
```

**header.c**

```c
#include <stdio.h>
#include "head.h"
	
	a = 18;
```

```c
#include "head.h"

main(){
	printf("%d \n", a);
}
```

This will be an error

```
In file included from test.c:9:0:
head.c:5:2: error: ‘a’ does not name a type
  a = 18;
```

### **.h** and **.cpp**

To compile with mupltiples header files

``g++ -o outputFile main.c other.c etc.c``

**head.h**

```c
void helloworld();
void display();
```

``head.c``

```c
#include <stdio.h>
#include "head.h"

void helloworld(){
	printf("Hello World \n");
}

void display(){
	printf("Display content \n");
}
```

**test.c**

```c
#include <stdio.h>
#include "head.h"

main(){
	helloworld();
	display();
}
```
Result

```
Hello World 
Display content 
```

# Macro

### Introduction 

````c
#define PRINT_HELLO_WORLD printf("Hello world")
#define PI 3.14159
#define a 6

main(){
	printf("%d \n", a);
	printf("%f \n", PI);
	PRINT_HELLO_WORLD;
}	
````

```
6
3.14159
Hello world
```

### Macro with past in parameter

```c
#define defineFunction(a) a+1

main(){
	int  result = defineFunction(6);
	printf("%d \n", result);
}	
```
```
7
```

```c
#define defineFunction(returnValue) returnValue+1

int a;

main(){
	printf("%d \n", defineFunction(a=14));
}
```

```
15
```