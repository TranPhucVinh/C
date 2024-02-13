# List of problem
* [Find min number in an array](#find-min-number-in-an-array)
* [Saddle point](saddle%point)
* Sort an array into **ascending** or **descending** order: Refer to [Sorting algorithms](https://github.com/TranPhucVinh/C/tree/master/Algorithms/Sorting%20algorithms#selection-sort)
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
# Saddle point

Find [saddle point](https://github.com/TranPhucVinh/C/tree/master/Data%20structure/Array) in a 2D array. Also check [saddle point document](https://github.com/TranPhucVinh/C/tree/master/Introduction/Data%20structure/Array#saddle-point) for the method to find saddle point inside a 2D array.

Program [saddle_point.c](saddle_point.c)
# [Using array to store Fibonacci sequence with recursively define will reduce execution time to 1 second, while Fibonacci recursive function takes tens of seconds to run](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Recursive%20function.md#fibonacci-sequence)
