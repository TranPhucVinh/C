# Examples

## Draw square with dots

```
   m 
********
*      *   n   
*      *     
********
```

```c
#include <stdio.h>
main() {
	int n, m;
	printf("enter m " );
	scanf("%d", &m);
	printf("enter n");
	scanf("%d", &n);
	for (int i = 1; i <= n ; i++)
	{
		if ((i == 1) || (i == n))
		{
			for (int j = 1; j <= m; j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else {
			for (int j = 1; j <= m; j++)
			{
				if ((j == 1 ) || (j == m))
				{
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			printf("\n");
		}
	}
}
```

## Find prime number

Find prime number with a limited of integer value

```c
#include <stdio.h>

main () {
	int n, count = 0;
	printf(" enter the limit value " );
	scanf("%d", &n);

	if (n <= 0)
	{
		printf("number must be greater than 0");
	}
	else
	{
		for (int i = 1; i <= n ; i++)
		{
			for (int j = 1; j <= i; j++)
			{
				if ((i % j) == 0)
				{
					count++;
				}
			}
			if (count == 2) {
				printf("%d ", i );
			}
			count = 0;
		}
	}
}
```

**Result**

```
enter the limit value 29
2 3 5 7 11 13 17 19 23 29
```

## Sum from 1 to n

Features: Number ``n`` entered as ``main()`` argument

Handle error:

* Must enter 1 parameter for n, less than 1 or more than 1 parameter is not accepted.
* Accept value of ``n`` is integer ``2147483647``
* Negative number is not accepted
* Invalid number ``123abc`` is not accepted (for the parsing operation of ``atoi()``)

For the max accepted number of ``2147483647``, the result must be ``unsigned long int``, not ``int``.

Program: [sum_from_1_to_n.c](https://github.com/TranPhucVinh/C/blob/master/Introduction/Examples/sum_from_1_to_n.c)

## Reverse number

Enter a number, print it in reverse order: 12345 => 54321

```c
#include <stdio.h>

main () {

	int a,b, number=0;

	printf("enter the value of a");
	scanf("%d",&a);

	while(a != 0)
	{
		b = a%10;
		a = a/10;
		number = number*10 + b;
	}
	printf("%d \n", number );
}
```
