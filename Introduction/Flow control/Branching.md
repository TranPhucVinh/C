# if else

## Short hand

```c
variable = (condition) ? expressionTrue : expressionFalse;
```
Example:

```c
int number = 20;
number = 20 ? printf("true") : printf("false");
```
## Double condition
```c
 int a = 3;
if (1 < a < 2) {
	printf("%d", a);// Result: 3 is printed out
}
```
**Analyse**: As we expected with Math logical, (1 < a < 3) is to whether a is inside the (1, 3). However, C interprets it diffently from the expected Math logic. 

In C, the expression (1 < a < 2) is interpreted differently than you might expect. It is evaluated in two steps:

* ``1 < a`` is evaluated first, which results in either 1 (true) or 0 (false).
* The result from step 1 is then compared to 2 in the second comparison.

For a = 3, the expression ``1 < a`` evaluates to ``1`` (``true``), and then ``1 < 2`` is ``true``, so the whole expression is true. Therefore, printf("%d\n", a); will be executed, printing 3.

To implement that logic, use that AND conditions instead:
```c
int a = 3;
if ((1 < a) && (a < 2)){
	printf(a);// Won't be printed as failed condition
}
```
# Set variable to 0 in a condition will return false

Condition when setting variable can be false (``0``) when the variable is set to ``0``:

```c
int a = 20, b = 0;

int main(){
    if (a=b) printf("true");
    else printf("false");
}
```
**Result**: ``false``

# Condition with !=0 number

```c
int main(){
	if(-12) printf("%s", "hello");
}
```
**Result**: ``hello``

Negative number results in true condition.
# switch case

Error ``jump to case label [-fpermissive]`` might happen if the instruction inside ``case`` is not put inside ``{}``. 

**Problem solved**

```c
switch (number){
	case 1:
    {
        display_string_1();
        break;
    }
	case 2:
	{
		display_string_2();
        break;
	}
}
```

String char can't be passed into ``switch case``.
# goto

## Simple goto example
```c
#include <stdio.h>

int main(){
    goto LABEL_0;
	LABEL_0:
		puts("Label 0");
    LABEL_1:    
        puts("Label 1");
        printf("outside goto\n");

	return 0;
}
```
**Result**

```
Label 0
Label 1
outside goto
```

To enter only ``LABEL_0``:

```c
goto LABEL_0;
	LABEL_0:
		puts("Label 0");
		return 0;		
    LABEL_1:    
        puts("Label 1");
        printf("outside goto\n");
		
	return 0;
```
## Infinite loop with goto

```c
#include <stdio.h>

int main() {
	PRINT_LABEL:
		puts("Enter print label");
	
	goto PRINT_LABEL;
	return 0;
}
```
