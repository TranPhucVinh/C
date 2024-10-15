A callback is a piece of executable code that is passed as an argument to other code, which is expected to call back (execute) the argument at some convenient time.

# Define the very first callback function

```c
#include <stdio.h>

void callback(){
	printf("Call back function \n");
}

void run_callback(void function()) {
	function();
}

int main() {  
    run_callback(callback);
}
```
# Call back function with parameters

Using normal function

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

# Handle callback by function pointer

Using function pointer to shorten the parameters passed into ``set_callback()``:

```c
#include <stdio.h>

void callback(int a, int b){
	printf("a: %d, b %d\n", a, b);
}

void set_callback(void function()){
   void (*display_pointer)(int a, int b);
   display_pointer = function;
   display_pointer(1, 2);
}

int main()
{
   set_callback(&callback);
// Or: set_callback(&callback);
}
```

Everything can also be called outside ``set_callback()``:

```c
#include <stdio.h>

void (*display_pointer)(int a, int b);

void callback(int a, int b){
	printf("a: %d, b %d\n", a, b);
}

void set_callback(void function()){
    display_pointer = function;
}

int main()
{  
    set_callback(callback);
    display_pointer(12, 34);
}
```
