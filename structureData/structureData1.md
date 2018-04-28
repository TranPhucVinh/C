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
