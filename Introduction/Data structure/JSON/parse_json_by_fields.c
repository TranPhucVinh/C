#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define ELEMENT_NUMBERS 1
#define FILE_NAME		"test.json"
#define FIELD_NAME		"data"

char *read_file(char *file_name);
void parse_string_field(char *json_string, char *field_name);
void parse_int_number_field(char *json_string, char *field_name);
void parse_array_field(char *json_string, char *field_name);

int main(){
   parse_array_field(read_file(FILE_NAME), FIELD_NAME);
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

void parse_array_field(char *json_string, char *field_name){
	const cJSON *array_field = NULL;
	cJSON *json = cJSON_Parse(json_string);
	cJSON *array_member = NULL;
    if (json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
	}
	array_field = cJSON_GetObjectItemCaseSensitive(json, field_name);
	int index = 0;
	if (cJSON_IsArray(array_field))
	{
		cJSON_ArrayForEach(array_member, array_field){
			char *array_member_string = cJSON_Print(array_member);
			printf("member %d: %s\n", index, array_member_string);
			index += 1;
		}
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