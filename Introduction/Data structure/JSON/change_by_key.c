#include <stdio.h>
#include "cJSON.h"

char *json_string = "{\"id\": 100, \"text\":\"hello, world\"}";

void get_int_number_field(char *json_string, char *field_name);
void edit_int_number_field(char *json_string, char *field_name, int value);

int main()
{  
	cJSON *json = cJSON_Parse(json_string);
	get_int_number_field(json_string, "id");
	edit_int_number_field(json_string, "id", 123);
	get_int_number_field(json_string, "id");
}

void get_int_number_field(char *json_string, char *field_name){
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

void edit_int_number_field(char *json_string, char *field_name, int value){
	cJSON *number_field = NULL;
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
		number_field->valueint = value;
	} else printf("Fail");

	char *jsonString = cJSON_Print(json);//Form a JSON 
	printf("temp %s", jsonString);
	// strcpy()
}