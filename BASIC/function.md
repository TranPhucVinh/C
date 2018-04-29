TARGET: We create function for factorial, fracture ( 1/1 +1/2 +1/3+.. +1/x)

```c
#include <stdio.h>

int factorial (int n)
{
	int m = 1;
	for (int i = 1; i <= n; i++)
	{
		m = m * i;
	}
	return m;
}

double fracture (int n)
{	
	double m = 0.0;
	for (double i = 1.0; i <= n; i++)
	{
		m = m + (1 / i); // if you declare int i=1 in for loop, the result of (1/i) will be kept as int
	}
	return m;
}

main()
{
	int n;
	scanf("%d", &n);
	printf("%d \n", factorial(n));
	printf("%lf \n", fracture(n));
}
```
OR
```c
#include <stdio.h>

int factorial (int n);
double fracture (int n);
	
main()
{
	int n;
	scanf("%d", &n);
	printf("%d \n", factorial(n));
	printf("%lf \n", fracture(n));
}
int factorial (int n)
{
	int m = 1;
	for (int i = 1; i <= n; i++)
	{
		m = m * i;
	}
	return m;
}

double fracture (int n)
{	
	double m = 0.0;
	for (double i = 1.0; i <= n; i++)
	{
		m = m + (1 / i); // if you declare int i=1 in for loop, the result of (1/i) will be kept as int
	}
	return m;
}
```
