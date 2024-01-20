# List of problem
* [Find min number in an array](Beginner%20level.md#find-min-number-in-an-array)
* [Saddle point](saddle%point)
# Find min number in an array

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
