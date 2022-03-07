#include "thingsboard.h"

#define HOST        "thingsboard.sysats.tech"
#define PORT        80

#define LOGIN_PATH        "/api/auth/login"
#define API			"/api/auth/user"

#define USER        "tranphucvinh96@gmail.com"
#define PASSWORD    "iotdev_admin"

#define BUFFSIZE        	4096 //Size must be big to get all JWT
#define TOKEN_SIZE			600
#define REFRESH_TOKEN_SIZE	500 

#define CUSTOMER_ID_SIZE	40
char token[TOKEN_SIZE], refreshToken[REFRESH_TOKEN_SIZE];

char *http_response = NULL;
char *get_customer_id(char *http_response, int customer_id_size);

int main(int argc, char *argv[]){
	_server_side_api_param_init(HOST, PORT, LOGIN_PATH, USER, PASSWORD);

	bzero(token, TOKEN_SIZE);
	bzero(refreshToken, REFRESH_TOKEN_SIZE);

	get_jwt(token, refreshToken, BUFFSIZE);

	http_response = http_request_for_api_with_jwt(API, "GET", token, BUFFSIZE);

	printf("%s\n", get_customer_id(http_response, CUSTOMER_ID_SIZE));
	free(http_response);

	return 0;
}

char *get_customer_id(char *http_response, int customer_id_size){
	//Get customerId
	char* temp_json_parsed = NULL;
	char* customer_id;

	customer_id =  (char*) malloc(customer_id_size * sizeof(char));
	bzero(customer_id, customer_id_size);

	cJSON *customer_id_object;

	temp_json_parsed = strstr(http_response, "customerId");
	strtok(temp_json_parsed, "{");
	temp_json_parsed = strtok(NULL, "}");
	int customer_id_json_size = strlen(temp_json_parsed) + 2;//2 for "{"" and "}"

	char customer_id_json[customer_id_json_size];
	bzero(customer_id_json, customer_id_json_size);

	strcat(customer_id_json, "{");
	strcat(customer_id_json, temp_json_parsed);
	strcat(customer_id_json, "}");
	
	cJSON *json_object = cJSON_Parse(customer_id_json);
	if (json_object == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
	}

	customer_id_object = cJSON_GetObjectItemCaseSensitive(json_object, "id");

	if (cJSON_IsString(customer_id_object) && (customer_id_object->valuestring != NULL))
	{
		strcpy(customer_id, customer_id_object->valuestring);
	} else printf("Fail to get token");

	return customer_id;
}