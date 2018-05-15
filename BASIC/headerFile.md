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

Compile normally with gnu (just ctrl+b)

Result

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
