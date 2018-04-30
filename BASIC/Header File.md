### Header file

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
