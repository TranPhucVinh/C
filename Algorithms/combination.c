#include <stdio.h>
void combination(int arr[], int arr_size, int data[], int start, int local_index, int r);

/* 
    @arr[]: Input array
    @arr_size: Size of int arr[]
    @start: Starting index of arr[]
    @local_index: Current index in local variable data[]
    @r: Size of a combination to be printed
*/
void combination(int arr[], int arr_size, int data[], int start, int local_index, int r)
{

	// Current combination is ready to be printed, print it
	if (local_index == r)
	{
		for (int j=0; j<r; j++) printf("%d ", data[j]);
		printf("\n");
		return;
	}

	/*
        The condition arr_size-i >= r-local_index make sure
        there are still element left to form the combination of r
    */
	for (int i=start; i<=arr_size-1 && arr_size-i >= r-local_index; i++)
	{
		data[local_index] = arr[i];
		combination(arr, arr_size, data, i+1, local_index+1, r);
	}
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5};
    int r = 3;
    int data[r];//An array to store all combination one by one
	int arr_size = sizeof(arr)/sizeof(arr[0]);
    combination(arr, arr_size, data, 0, 0, r);
}
