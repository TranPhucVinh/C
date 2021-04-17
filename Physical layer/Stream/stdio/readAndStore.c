#include <stdio.h>

#define MEMBER      3
#define STRING_SIZE 12

char stringArray[MEMBER][STRING_SIZE];
char filePath[] = "json.txt";

int index;
FILE *fptr; //file pointer

int main(){
   fptr = fopen(filePath, "r");

   while (index < MEMBER){
      if (fgets(stringArray[index], STRING_SIZE, fptr) == NULL) break;
      else {
         //Remove the \n character
         if(stringArray[index][STRING_SIZE-2] == '\n') stringArray[index][STRING_SIZE-2] ='\0';
         index++;
      }   
   }
   for (int i=0; i < MEMBER; i++){
		printf("stringArray[%i]: %s \n", i, stringArray[i]);
	}
}