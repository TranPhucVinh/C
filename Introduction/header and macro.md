### Basic header file

``head.h``

```c
void helloworld(){
	printf("Hello World");
}
```

``main.c``

```c
#include <stdio.h>
#include "head.h"

main(){
	helloworld();
}
```

**Result**

```
Hello World
```

### Header file

Can't compile normally with ``ctrl+B``

To compile with mupltiples header files

``g++ -o outputFile main.c other.c etc.c``

``head.h``

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

``test.c``

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

# macro

````c
#define PRINT_HELLO_WORLD printf("Hello world")
#define PI 3.14159
````

Used to infer a function in preprocessor, all PRINT_HELLO_WORLD will be replaced by ``printf("Hello world")`` in source code.