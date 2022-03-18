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

void callback(int a, int b){
	printf("a: %d, b %d\n", a, b);
}

void run_callback(void function(), int a, int b){
	function(a, b);
}

int main()
{  
    run_callback(callback, 10, 11);
}
```
