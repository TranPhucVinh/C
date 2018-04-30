```c
#include <stdio.h>
struct add
{
	int num1;
	int num2;
} add1, add2, result;
void resultNumber(struct add number1, struct add number2, struct add resultNum);
main(){
    printf("Enter number 1 of group 1: ");
    scanf("%d", &add1.num1);
    printf("Enter number 2 of group 1: ");
    scanf("%d", &add1.num2);
    printf("Enter number 1 of group 2: ");
    scanf("%d", &add2.num1);
    printf("Enter number 2 of group 2: ");
    scanf("%d", &add2.num2);
    resultNumber(add1, add2, result);
    printf("number 1 %d; number 2 %d", result.num1, result.num2);
}

void resultNumber(struct add number1, struct add number2, struct add resultNum){
	resultNum.num1 = number1.num1 + number2.num1;
	resultNum.num2 = number1.num2 + number2.num2;
}
```

Result
```
Enter number 1 of group 1: 1
Enter number 2 of group 1: 3
Enter number 1 of group 2: 5
Enter number 2 of group 2: 9
number 1 0; number 2 0
```

=> This is the problem with pointer

### Solve

```c
#include <stdio.h>

struct complexNumber{
	int real, imagine;
} complex1, complex2, result;

void resultNumber(struct complexNumber complex1, struct complexNumber complex2, struct complexNumber *result);

main() {
	printf("Enter complex1 real ");
	scanf ("%d", &complex1.real);
	printf("Enter complex1 imagine ");
	scanf("%d", &complex1.imagine);
	printf("Enter complex2 real ");
	scanf ("%d", &complex2.real);
	printf("Enter complex2 imagine ");
	scanf("%d", &complex2.imagine);
	resultNumber( complex1, complex2, &result);
	printf("Result number: %d + %di \n", result.real, result.imagine);
}

void resultNumber(struct complexNumber complex1, struct complexNumber complex2, struct complexNumber *result){
	result->real = complex1.real + complex2.real;
	result->imagine = complex1.imagine + complex2.imagine;
}
```

```
Enter complex1 real 5
Enter complex1 imagine 6
Enter complex2 real 45
Enter complex2 imagine 23
Result number: 50 + 29i
```
