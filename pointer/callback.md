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
    void (*p)() =abs;
	  helloWorld(p);
}
```
