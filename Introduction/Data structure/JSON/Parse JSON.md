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

## Parse JSON by fields from a file

Program: ``parse_json_by_fields.c``