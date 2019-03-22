### Drawing 

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

### Simple function

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
	
main(){
	int n;
	scanf("%d", &n);
	printf("%d \n", factorial(n));
	printf("%lf \n", fracture(n));
}
int factorial (int n){
	int m = 1;
	for (int i = 1; i <= n; i++)
	{
		m = m * i;
	}
	return m;
}

double fracture (int n){	
	double m = 0.0;
	for (double i = 1.0; i <= n; i++)
	{
		m = m + (1 / i); // if you declare int i=1 in for loop, the result of (1/i) will be kept as int
	}
	return m;
}
```

### Reverse number

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