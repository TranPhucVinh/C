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
Must not use double condition in one check:
```c
// MUST NOT DO THAT
int a = 3;
if ((1 < a < 2)){// This condition will always return true, and give no compilation error
	printf(a);// Won't be printed as failed condition
}

```
Use that instead:
```c
int a = 3;
if ((1 < a) && (a < 2)){
	printf(a);// Won't be printed as failed condition
}
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

**Draw a rectangle with dots**
```
column  
***
* * row
* *
***
```'
```c
#include <stdio.h>
int main() {
	int column = 3;
    int row = 4;

	for (int i = 1; i <= row ; i++)
	{
		if ((i == 1) || (i == row))
		{
			for (int j = 1; j <= column; j++){
				printf("*");
			}
			printf("\n");
		}
		else {
			for (int j = 1; j <= column; j++)
			{
				if ((j == 1 ) || (j == column)) {
					printf("*");
				}
				else printf(" ");
			}
			printf("\n");
		}
	}
}
```
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
