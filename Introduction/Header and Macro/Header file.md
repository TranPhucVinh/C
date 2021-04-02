**Define function, variable in ``.h`` file.**

``head.h``

```c
#include <stdio.h>

void helloworld(){
	printf("Hello World \n");
}

int value = 6;
```

``main.c``

```c
#include "head.h"

int main(){
	helloworld(); //Hello World
	printf("%d \n", value); //6
}
```

**Define function, variable in ``.c`` file.**

``head.h``

```cpp
#include <stdio.h>

void helloworld();
```

``head.c``

```cpp
#include "head.h"

void helloworld(){
    printf("Hello World \n");
}
```

``main.c``

```c
#include "head.h"

int main(){
	helloworld(); //Hello World
}
```