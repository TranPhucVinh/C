#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 3
#define COLUMN_SIZE 4

int **init_array(int row_size, int column_size);
void add_value(int **array, int row, int column, int value);
void update_value(int **array, int row, int column, int value);
void print_array(int **array, int row, int column);
void delete_array();

int main(){
	int **array;
	array = init_array(ROW_SIZE, COLUMN_SIZE);

	int index = 0;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int column = 0; column < COLUMN_SIZE; column++){
			add_value(array, row, column, index);
			index += 1;
		}	
	}

	print_array(array, ROW_SIZE, COLUMN_SIZE);
    delete_array(array, ROW_SIZE);
}

/*
	Memory initialization for array
	@row_size:
	@column_size:
	Return: A memory allocated 2D array
*/
int **init_array(int row_size, int column_size){
	int **array = (int**) malloc(ROW_SIZE * sizeof(int*));

	for (int row = 0; row < ROW_SIZE; row++){
		array[row] = (int*) malloc(COLUMN_SIZE * sizeof(int));
	}
	return array;
}

void add_value(int **array, int row, int column, int value){
	array[row][column] = value;
}

void update_value(int **array, int row, int column, int value){
	array[row][column] = value;
}

void print_array(int **array, int row_size, int column_size){
	for (int row = 0; row < row_size; row++){
		for (int column = 0; column < column_size; column++) 
			printf("array[%d][%d]: %d\n", row, column, array[row][column]);
	}
}

void delete_array(int **array, int row_size){
	//Free all allocated memory location of the rows
	for (int row = 0; row < row_size; row++){
		free(array[row]);
	}

    //Finally free the memory location of the array
    free(array);
}