Use pointer to enter the values in array and display these values on screen

```c
#include <stdio.h>

void main() {
	int n, *p1, *p2, i;
	int a[20];
	printf(" Number of members in array: ");
	scanf("%d", &n);
	p1 = p2 = &a[0];
	printf("Enter the value of every member: " );
	for (i = 0; i < n; i++)
	{
		scanf("%d", p1);
		p1++;
	}
	printf("Value of all members in array: ");
	for (i = 0; i < n; i++)
	{
		printf("%d ", *p2 );
		p2++;
	}
}
```
