## Parse a JSON string with multiple fields

```c
#include <stdio.h>
#include "cJSON.h"

const cJSON *id, *text;

char *json_string = "{\"id\": 100, \"text\":\"hello, world\"}";
void parse_string_field(char *json_string, char *field_name);
void parse_int_number_field(char *json_string, char *field_name);

int main(){
	parse_string_field(json_string, "text");
	parse_int_number_field(json_string, "id");
}

void parse_string_field(char *json_string, char *field_name){
	const cJSON *string_field = NULL;
	cJSON *json = cJSON_Parse(json_string);
    if (json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
	}

	string_field = cJSON_GetObjectItemCaseSensitive(json, field_name);
	
	if (cJSON_IsString(string_field) && (string_field->valuestring != NULL))
	{
		printf("string: \"%s\"\n", string_field->valuestring);
	} else printf("Fail");
}

void parse_int_number_field(char *json_string, char *field_name){
	const cJSON *number_field = NULL;
	cJSON *json = cJSON_Parse(json_string);
    if (json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
	}

	number_field = cJSON_GetObjectItemCaseSensitive(json, field_name);
	if (cJSON_IsNumber(number_field) && (number_field->valueint != 0))
	{
		printf("int number: %d\n", number_field->valueint);
	} else printf("Fail");
}
```

## Parse JSON by fields from a file

Program: ``parse_json_by_fields.c``