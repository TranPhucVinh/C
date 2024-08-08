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
