#include <stdio.h>

/*
    Allocate array with size bigger than its current total member
    for inserting
*/
int array[100] = {1,3,5,7,8};
int array_size = 5;

//Display array before inserting
void display_array(int arr[], int arr_size){
    for(int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insert_member(int arr[], int *arr_size, int insert_index, int insert_val){
    int j = *arr_size;
    while(j >= insert_index){
        array[j+1] = array[j];
        j--;
    }
	
    array[insert_index] = insert_val;
    *arr_size += 1;
}

int main() {   
    printf("Array before adding: ");
    display_array(array, array_size);
    insert_member(array, &array_size, 2, 10);
    printf("Array after inserting: ");
    display_array(array, array_size);
}
