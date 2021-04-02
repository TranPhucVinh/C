**Define function, variable in ``.h`` file.**

``head.h``

```c
#include <stdio.h>

void displayString(){
	printf("Hello World \n");
}

int value = 6;
```

``main.c``

```c
#include "head.h"

int main(){
	displayString(); //Hello World
	printf("%d \n", value); //6
}
```

**Define function in ``.c`` file.**

``head.h``

```cpp
#include <stdio.h>

void displayString();
```

``head.c``

```cpp
#include "head.h"

void displayString(){
    printf("Hello World \n");
}
```

``main.c``

```c
#include "head.h"

int main(){
	displayString(); //Hello World
}
```

For variables defined in header file, check the related ``extern`` document.