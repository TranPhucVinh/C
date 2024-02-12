# Condition changed during execution

Condition of a loop can be changed normally. Example:

```c
//This program will run as an indefinite loop
int i = 0;
int a = 10;
while (i < a){
	i += 1;
	a += 1;
	printf("i %d, a %d\n", i, a);
}
```

Take [Find the nth digit of an infinite integer sequence](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Medium%20level.md#find-the-nth-digit-of-an-infinite-integer-sequence) as an example when the condition is changed during execution.

# A special false condition

Condition when setting variable can be false (``0``) when the variable is set to ``0``:

```c
int a = 20, b = 0;

int main(){
    if (a=b) printf("true");
    else printf("false");
}
```
**Result**: ``false``

# Condition with int number

```c
int main(){
	if(-12) printf("%s", "hello");
}
```
**Result**: ``hello``

Negative number results in true condition.

# if else

Short hand

```c
variable = (condition) ? expressionTrue : expressionFalse;
```
Example:

```c
int number = 20;
number = 20 ? printf("true") : printf("false");
```

# return

The ``return`` statement stops the execution of a function and returns a value from that function.

Return in ``void``

```c
void returnNumber(){
	int a = 0, b=0;

	if ((a==0)&&(b==0)){
	 	return;
	 }
	printf("inside \n");
}

int main() {
	returnNumber();
	printf("hello world");
}
```

**Result**

```
hello world
```

If ``a==0`` and ``b==0``, it return in ``void returnNumber()`` and end the function.

If we ommitted ``if ((a==0)&&(b==0))``, the result will be

```
inside
hello world
```

# for

Omit 1st expression

```c
int index = 0;
for(; index < 10; index++){
	printf("index: %d\n", index);
}
```
**Result**: Print out from ``0`` to ``9``.

Omit 2nd expression, the 2nd expression now is ``true``

```c
for(int index = 0;;index++){
        printf("index: %d\n", index);
}
```    
Omit 3nd expression
```c
int index = 0;
for(int index = 0;index<10;){
	printf("index: %d\n", index);
}
```
**Result**: Print out ``0`` forever.

``for(;;)`` is equal to ``while(1)``.

# switch

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

# break

```c
for (i=0; i<10; i++){
		if(i==5) break;
		printf("i value is %d \n", i);
	}
```

```
i value is 0 
i value is 1 
i value is 2 
i value is 3 
i value is 4 
```

# continue

```c
for (i=0; i<10; i++){
		if(i==5) continue;
		printf("i value is %d \n", i);
	}
```

```
i value is 0 
i value is 1 
i value is 2 
i value is 3 
i value is 4 
i value is 6 
i value is 7 
i value is 8 
i value is 9 
```

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

int main(){
	PRINT_LABEL:
		puts("Enter print label");
	
	goto PRINT_LABEL;
	return 0;
}
```

Notice, ``goto label`` must be put in the same scope of ``goto``.

# assert

``assert()`` is a macro that is used to check specific conditions at runtime (when a program is under execution) and is very useful while debugging a program. 

To ``assert()``, you must include ``assert.h``

``assert(condition)``:

* If ``condition==true``: Keep program execution
* If ``condition==false``: Program terminates, and an error message is displayed on the screen specifying the filename, the line number, the function name, the condition that does not hold.

```c
#include <stdio.h>
#include <assert.h>
 
int main() {
  int a, b;
 
  printf("Input two integers to divide: \n");
  scanf("%d%d", &a, &b);
 
  assert(b != 0);
 
  printf("%d/%d = %.2f\n", a, b, a/(float)b);
 
  return 0;
}
```

If error, output: ``Assertion failed: b != 0, file test.c, line 10``

Always terminates with ``assert(0)``

```c
printf("Hello, World ! \n");
assert(0);
```
**Output**

```
Hello, World !
Assertion failed: 0, file test.c, line 6
```
