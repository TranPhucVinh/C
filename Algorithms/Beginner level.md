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

## Find min number in an array

```c
#include <stdio.h>

void set_value_for_array(int *array, int n){
	for (int i=0;i<n;i++){
		printf("Enter value array[%d]:",i );
		scanf("%d", &array[i]);
	}
}
void main() {
	int n;
	printf("enter number n:");
	scanf("%d", &n);
	int array[n];
	set_value_for_array(array, n);

	for (int i=0; i < n; i++){
		printf("Value of member %d is %d\n", i, array[i]);
	}

    int min;
    min = array[0];
    for (int i=1; i < n; i++){
        if (min >= array[i]) min = array[i];
	}
    printf("min: %d\n", min);
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