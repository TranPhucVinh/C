#include <stdio.h>

#define SIZE 6

int array[6] = {34, 12, 135, 45, 1, 9};

int main(){
    printf("Array before: ");
    for (int i=0; i < SIZE; i++)
	{
		printf("%d ", array[i]);
	}
    printf("\n");

	for (int i=0; i < SIZE; i++)
	{
		int max = array[i];
		int pos = i;
		for (int j=i+1; j < SIZE; j++)
		{
			if (max < array[j]){
				max = array[j];
				pos = j;
			}
		}	
			if (pos != i){
				int temp = array[i];
				array[i] = max;
				array[pos] = temp;
			}
	}

    printf("Array after: ");
	for (int i=0; i < SIZE; i++)
	{
		printf("%d ", array[i]);
	}
    printf("\n");
}