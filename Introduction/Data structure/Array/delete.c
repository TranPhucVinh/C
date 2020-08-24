#include <stdio.h>

int array[] = {1,3,5,7,8};
int deleteIndex = 2;
int i, j;
size_t arraySize = sizeof(array)/sizeof(array[0]);

void arrayBeforeDeleting(){
  printf("Array before deleting: ");

  for(i = 0; i < arraySize; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void arrayAfterDeleting(){
  j = deleteIndex;

  while(j <= arraySize){
    array[j] = array[j+1];
    j++;
  }

  arraySize--;

  printf("Array after deleting: ");

  for(i = 0; i < arraySize; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

int main() {
  arrayBeforeDeleting();
  arrayAfterDeleting();
}