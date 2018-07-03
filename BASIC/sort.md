### Select sort

```c
#include <stdio.h>

main(){
	int i, j, n, array[100], max, pos, temp;
	printf("Enter the number of members: ");
	scanf("%d", &n);
	printf("Enter the value of each member: ");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	for (i=0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	for (i=0; i<n-1; i++)
	{
		max = array[i];
		pos = i;
		for (j=i+1; j<n; j++)
		{
			if (max < array[j]){
				max = array[j];
				pos = j;
			}
		}	
			if (pos != i){
				temp = array[i];
				array[i] = max;
				array[pos] = temp;
			}
	}
	for (i=0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
}
```
