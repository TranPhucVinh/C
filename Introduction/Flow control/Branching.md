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
if ((1 < a < 2)){
	printf(a);// Result: 3 is printed out
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

# Short-circuiting
Short-circuiting is one of the optimization steps of the compiler, in this step unnecessary calculation is avoided during the evaluation of an expression. Expression is evaluated from left to right. It works under && and || operator, when the value of the expression can be calculated certainly by only evaluating parts of the expression.
```cpp
int a = 1, b = 1, c = 1;

if (a == b || c++) {
	printf("%d\n", c);// 1
}
printf("%d\n", c);// 1

if (a != b && c++) {
	printf("%d\n", c);// 1
}
printf("%d\n", c);// 1
```
``(a == b || c++)`` as ``a`` is equal to ``b`` so ``||`` is always right, then ``c++`` is not calculated.

``(a != b && c++)`` as ``a != b`` is wrong so ``&&`` is alway wrong, then ``c++`` is not calculated.

If the left side of the || expression is wrong/&& expression is true, the right side will be calculated. 
```c
int a = 1, b = 1, c = 1;

if (a != b || c++) {
	printf("%d\n", c);// 2
}

if (a == b && c++) {
	printf("%d\n", c);// 3
}
```
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
