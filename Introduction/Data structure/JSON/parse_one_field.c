#include <stdio.h>
#include "cJSON.h"

const cJSON *name = NULL;

const char *jsonString = "{\"string\":\"hello, world\"}";

int main(){
  cJSON *json = cJSON_Parse(jsonString);
  name = cJSON_GetObjectItemCaseSensitive(json, "string");
  if (json == NULL)
  {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
        fprintf(stderr, "Error before: %s\n", error_ptr);
    }
  }

  if (cJSON_IsString(name) && (name->valuestring != NULL))
  {
    printf("string: \"%s\"\n", name->valuestring);
  } else printf("Fail");
}