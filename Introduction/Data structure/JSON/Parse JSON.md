## Parse a JSON string with multiple fields

```c
#include <stdio.h>
#include "cJSON.h"

const cJSON *id, *text;

const char *jsonString = "{\"id\": 100, \"text\":\"hello, world\"}";

int main(){
  cJSON *json = cJSON_Parse(jsonString);

  //For text field
  text = cJSON_GetObjectItemCaseSensitive(json, "text");
  if (json == NULL)
  {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
        fprintf(stderr, "Error before: %s\n", error_ptr);
    }
  }

  if (cJSON_IsString(text) && (text->valuestring != NULL))
  {
    printf("string: \"%s\"\n", text->valuestring);
  } else printf("Fail");

  //For id field
  id = cJSON_GetObjectItemCaseSensitive(json, "id");
  if (json == NULL)
  {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
        fprintf(stderr, "Error before: %s\n", error_ptr);
    }
  }

  if (cJSON_IsNumber(id))
  {
    printf("id: %d\n", id->valueint);
  } else printf("Fail");
}
```

## Parse JSON value from a file

File ``json.txt``:

```json
{"string": "Text"}
```

```c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define ELEMENT_NUMBERS 1
#define FILE_NAME		"json.txt"
#define FIELD_NAME		"string"

char *read_file(char *file_name);
void parse_string_field(char *jsonString, char *fieldName);

int main(){
   parse_string_field(read_file(FILE_NAME), FIELD_NAME);
}

void parse_string_field(char *jsonString, char *fieldName){
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

char *read_file(char *file_name){
    FILE *fp;

    fp = fopen(file_name, "r");
    if (fp != NULL) {
        fseek(fp, 0L, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        char *buffer;
        buffer = (char *) malloc(file_size);
        bzero(buffer, file_size);//delete garbage value

        fread(buffer, file_size, ELEMENT_NUMBERS, fp);//Will read ELEMENT_NUMBERS*file_size from fp
        fclose(fp);
        return buffer;
   } else {
       printf("Unable to open file %s", file_name);
       return "NULL";
    }
}
```