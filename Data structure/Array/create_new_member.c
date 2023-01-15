#include <stdio.h>

int array[] = {1,3,5,7,8};
int addIndex = 2;
int newMemberValue = 10;
int i, j;
size_t arraySize = sizeof(array)/sizeof(array[0]);

void arrayBeforeAdding(){
  printf("Array before adding: ");
	
  for(i = 0; i < arraySize; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void arrayAfterAdding(){
  arraySize++;
	
  while(j >= addIndex){
    array[j+1] = array[j];
    j--;
  }
	
  array[addIndex] = newMemberValue;
   
  printf("Result after adding: ");
	
  for(i = 0; i < arraySize; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

int main() {   
  arrayBeforeAdding();
  arrayAfterAdding();
}