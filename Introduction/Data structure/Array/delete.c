#include <stdio.h>

int array[] = {1,3,5,7,8};
size_t array_size = sizeof(array)/sizeof(array[0]);

void display_array(){
  for(int i = 0; i < array_size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void delete_member(int delete_index){
    while(delete_index < array_size){
        array[delete_index] = array[delete_index+1];
        delete_index++;
    }

    array_size--;
}

int main() {
    printf("Array before deleting: ");
    display_array();
    delete_member(2);
    printf("Array after deleting: ");
    display_array();
}
