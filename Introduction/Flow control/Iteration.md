# [for](for%20loop.md)
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

int main(){* Short circuiting
* assert
	PRINT_LABEL:
		puts("Enter print label");
	
	goto PRINT_LABEL;
	return 0;
}
```
