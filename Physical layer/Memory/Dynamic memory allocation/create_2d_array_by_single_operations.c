#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 3
#define COLUMN_SIZE 4

int main(){
	int **array = (int**) malloc(ROW_SIZE * sizeof(int*));

	for (int row = 0; row < ROW_SIZE; row++){
		array[row] = (int*) malloc(COLUMN_SIZE * sizeof(int));
	}

	int index = 0;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int column = 0; column < COLUMN_SIZE; column++){
			array[row][column] = index;
			index += 1;
		}	
	}

	for (int row = 0; row < ROW_SIZE; row++){
		for (int column = 0; column < COLUMN_SIZE; column++) 
			printf("array[%d][%d]: %d\n", row, column, array[row][column]);
	}
    
    //Free all allocated memory location of the rows
	for (int row = 0; row < ROW_SIZE; row++){
		free(array[row]);
	}

    //Finally free the memory location of the array
    free(array);
}