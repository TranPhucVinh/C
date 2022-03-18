### Run a simple callback function

```c
#include <stdio.h>

void callback(){
	printf("Call back function \n");
}

void run_callback(void function()){
	function();
}

int main()
{  
    run_callback(callback);
}
```
### Call back function with parameters

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
