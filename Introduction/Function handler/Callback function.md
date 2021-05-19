**Example 1**: Create a very basic call back function

```c
#include <stdio.h>

void callbackFunction(){
	printf("Call back function \n");
}

void testFunction(void function()){
	function();
}

main()
{  
    testFunction(callbackFunction);
}
```
**Example 2**: Call back function with parameter

```c
#include <stdio.h>

void callbackFunction(int intParam1, int intParam2){
	printf("int parameter 1 is %d\n", intParam1);
	printf("int parameter 2 is %d\n", intParam2);
}

void testFunction(void function(), int param1, int param2){
	function(param1, param2);
}

main()
{  
    testFunction(callbackFunction, 12, 13);
}
```