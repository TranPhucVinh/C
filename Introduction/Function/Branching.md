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
# [for](for%20loop.md)
# break
**break** will break the execution of its current loop
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
