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

**Result:** ``Hello world``

This can be replaced as ``helloWorld(abs);``

In c compiler, callback function must be used with pointer as the function need to know the address of the callback function to call it.
