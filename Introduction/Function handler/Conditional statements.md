### condition with int number

```c
int main(){
	if(-12) printf("%s", "hello");
}
```
**Result**: ``hello``

Negative number results in true condition.

## return

The **return statement** stops the execution of a function and returns a value from that function.

Return in **void**

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

## continue vs break

### break

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

### continue

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

### goto

Infinite loop with ``goto``

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

### assert

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