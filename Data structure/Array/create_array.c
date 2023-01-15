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
		printf("Value of member %d is %d \n", i, array[i]);
	}
}