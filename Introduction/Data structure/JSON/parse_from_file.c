#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cJSON.h"

#define bufferSize 100

char fileName[] = "json.txt";
char fieldName[] = "string";

char *readBuffer;

void readFile(char *filename, char *readBuffer);
void parseJSON(char *jsonString, char *fieldName);

int main(){
   readBuffer = (char*) malloc (bufferSize * sizeof(char));
   readFile(fileName, readBuffer);  
   parseJSON(readBuffer, fieldName);
   // printf("%s", readBuffer); 
}

void readFile(char *filename, char *readBuffer){
   int fileDescription = open(fileName, O_RDONLY);

   if (readBuffer == NULL) {
     fprintf(stderr, "Unable to allocate memory for readBuffer\n");
     return -1;
   }

   if(fileDescription < 0) return 1;

   read(fileDescription, readBuffer, bufferSize);
}

void parseJSON(char *jsonString, char *fieldName){
   const cJSON *field = NULL;

   cJSON *json = cJSON_Parse(jsonString);
   field = cJSON_GetObjectItemCaseSensitive(json, fieldName);
   if (json == NULL)
   {
      const char *error_ptr = cJSON_GetErrorPtr();
      if (error_ptr != NULL)
      {
         fprintf(stderr, "Error before: %s\n", error_ptr);
      }
   }

   if (cJSON_IsString(field) && (field->valuestring != NULL))
   {
      printf("string: \"%s\"\n", field->valuestring);
   } else printf("Fail");
}