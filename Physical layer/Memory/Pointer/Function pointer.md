# Declare function pointer

```c
#include <stdio.h>

int add_int_numbers(int a, int b){
	return a+b;
}

int subtract(int a, int b){
	return a-b;
}

double add_numbers(int a, double b){
	return a+b;
}

void display_number(int a, int b){
	printf("a: %d, b: %d\n", a, b);
}

int main()
{  
    int (*p)(int, int);
    p = add_int_numbers;
    printf("%d \n",p(5,6)); //11
    p = subtract;
    printf("%d \n",p(5,8)); //-3

    double (*pointer)(int, double);
    pointer = add_numbers;
    printf("%.2f \n", pointer(8, 9.89)); //17.89

	void (*display_pointer)(int a, int b);
	display_pointer = display_number;
	display_pointer(12, 13);
}
```

# Function pointer as argument

```c
#include <stdio.h>

void abs(){
	printf("Hello world");
}

void helloWorld (void (*function)()){
	function();
}
int main()
{ 	
    void (*p)() = abs;
    helloWorld(p);
}
```

**Result:** ``Hello world``

This can be replaced as ``helloWorld(abs);``:

```c
int main()
{
   helloWorld(abs);
}
```
# Function pointer for polymorphism by callback function
Function pointer is used to define a function multiple times, i.e polymorphism, by callback function
```c
#include <stdio.h>

void (*polymorphism)();

void function_define(void function()){
    polymorphism = function;
}

void display_str_1(){
    printf("Display string 1\n");
}

void display_str_2(){
    printf("Display string 2\n");
}

int main()
{ 	
    function_define(display_str_1);
    polymorphism();
    function_define(display_str_2);
    polymorphism();
}
```
```
Display string 1
Display string 2
```
