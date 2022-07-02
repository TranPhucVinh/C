#include <stdio.h>

#define SIZE 10

int array[SIZE] = {125, 3, 13, 2, 4, 0, 5, 13, 2, 10};

int arrange_required = 0;

int main(){
    printf("Array before: ");
    for (int i=0; i < SIZE; i++)
	{
		printf("%d ", array[i]);
	}
    printf("\n");

    while (!arrange_required){
        for (int i = 0; i < SIZE - 1; i++)
        {
            int temp = array[i];
            if (temp > array[i+1]){
                array[i] = array[i+1];
                array[i+1] = temp;
                arrange_required += 1;
            }
        }
        if (arrange_required > 0) arrange_required = 0;
        else arrange_required = 1;
    }

    printf("Array after: ");
	for (int i=0; i < SIZE; i++)
	{
		printf("%d ", array[i]);
	}
    printf("\n");
}