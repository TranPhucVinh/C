### Macro functions with arguments

```c
#define defineFunction(a) a+1

int result = defineFunction(6);
printf("%d \n", result); //7
```

Argument can be passed to the marco function

```c
int a;
printf("%d \n", defineFunction(a=6)); //7
```

Perform multiples instruction inside a macro function

```c
#include <stdio.h>
#define defineFunction(a) a+1; printf("Line 1\n"); printf("Line 2\n")

int main(){
   int result = defineFunction(6);
   printf("%d", result);
}		
```

```
Line 1
Line 2
7
```

### Pass-by-reference issue doesn't happen in macro function

```c
#include <stdio.h>
 
#define defineFunction(a) a=a+1

int main()
{
    int b = 1;
    defineFunction(b);
    printf("%d \n", b); //2
    return 0;
}
```

### Using if else inside macro function

To use if else, the macro fucntion must be the expression, which is ``({ })``

```c
#include <stdio.h>

//return_number now works as return keyword like in normal function
#define INT_NUMBER(number) 		({\
	int return_number;\
	if (number == 10) return_number = 123;\
	else return_number = 456;\
	return_number;\ 
})

int main()
{  
	int number = 10;
	printf("%d \n", INT_NUMBER(number));//123
}
```

### Macro function side effect

```c
#define SQUARE(x) (x*x)

printf("square(%d) = %d", 3, SQUARE(1+2));//5
```

Although we expect the result is ``9`` but the result is actually ``5 = 1 + 1*2* + 2``

Problem solve:

```c
#define SQUARE(x) ((x)*(x))
printf("square(%d) = %d", 3, SQUARE(1+2));//9
```

Unable to get the right value from macro in if else condition although correct value is returned:

```c
#include <stdio.h>

#define VAL_SET(addr,pin) ((*(addr+13))>>pin)&1

int main(){
    //Form an array to set valid value for *(ptr+13) to 13
    int number[14];
    for (int i = 0; i < 14; i++){
        number[i] = i;
    }   
	int *ptr = &number[0];
    printf("%d %d\n", *ptr, *(ptr+13));
    if (VAL_SET(ptr, 1) == 0) printf("VAL_SET(ptr, 1) = 0\n");
    else printf("VAL_SET(ptr, 1) != 0, VAL_SET(ptr, 1) is %d\n", VAL_SET(ptr, 1));
}
```

With ``int *ptr = &number[0]``, then ``*ptr`` is ``0``, ``*(ptr+13)`` is ``13``, ``*(addr+13))>>pin`` is then ``*(ptr+13))>>1`` returns ``0``, ``&1`` to the result will return ``0``. Although ``VAL_SET(ptr, 1)`` returns ``0``, the ``else`` condition is reached.

Related issue: [Controled LED with button by using macro direct memory access in Raspbian](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Physical%20layer/GPIO/direct_register_access_control_led_with_button.c), the same macro issue happens with ``GPIO_GET(addr,pin)``.

### Choosing between macro and function

Macro create the inline code which will the shorten the execution time of the program, while the function takes longer time to execute.

If a macro is executed 20 times, then 20 lines of macro code will be added to the preprocessor which will expand the size of the compiled program (``.exe``, ``.dll``, ``.lib``,...). However, the time is saved as macro doesn't require stack call

If a function is called 20 times, only 1 copy of that function will be used inside the program, the program then require more time as it needs to call stack every time that function is needed. Using function which will make the program size smaller than using the macro correspondingly.

It depends on execution times and program size requirement to choose between macro and function.

### Using macro to define

Check [Using macro to define](https://github.com/TranPhucVinh/C/blob/master/Introduction/Macro/Using%20macro%20to%20define.md)

### Can't use recursive in macro

This example with recursive function for sum from 1 to n results in failure operation:

```c
#include <stdio.h>

#define sum_of_numbers(number) (number = 1) ? 1 : number + sum_of_numbers(number - 1)

int main()
{  
	int number = 20;
	printf("Sum from 1 to %d: %d", number, sum_of_numbers(number));
}
```
**Compile**: This give warning in GCC

```c
test.c: In function ‘main’:
test.c:3:60: warning: implicit declaration of function ‘sum_of_numbers’ [-Wimplicit-function-declaration]
 #define sum_of_numbers(number) (number = 1) ? 1 : number + sum_of_numbers(numbe
                                                            ^
test.c:8:41: note: in expansion of macro ‘sum_of_numbers’
  printf("Sum from 1 to %d: %d", number, sum_of_numbers(number));
```

**Result**: ``Sum from 1 to 1: 1``

This program gives error in G++: ``error: ‘sum_of_numbers’ was not declared in this scope``
