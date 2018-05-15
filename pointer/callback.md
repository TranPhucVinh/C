### Basic without pointer

```c
#include <stdio.h>

void hello(){
	printf("Hello world \n");
}

void helloWorld (void function()){
	function();
}

main()
{  
    helloWorld(hello);
}
```
**Result**
```
Hello world
```

### With pointer

```c
#include <stdio.h>

void abs(){
	printf("Hello world");
}

void helloWorld (void (*function)()){
	function();
}
main()
{ 	
    void (*p)() = abs;
    helloWorld(p);
}
```

**Result:** ``Hello world``

This can be replaced as ``helloWorld(abs);``
