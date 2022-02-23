``typedef`` can be used to give a type a new name.

```c
#include <stdio.h>

typedef int integer;

integer displayFunction();

int main() {
	integer a = 19;
	printf("%d\n", a); //19
    printf("%d\n", displayFunction()); //4
}

integer displayFunction(){
    return 4;
}
```
