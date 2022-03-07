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
char *get_all_customer_devices(char *customer_id);

int main(int argc, char *argv[]){
	_server_side_api_param_init(HOST, PORT, LOGIN_PATH, USER, PASSWORD);

	bzero(token, TOKEN_SIZE);
	bzero(refreshToken, REFRESH_TOKEN_SIZE);

	get_jwt(token, refreshToken, BUFFSIZE);

	http_response = http_request_for_api_with_jwt(API, "GET", token, BUFFSIZE);

	char *customer_id;

	customer_id = get_customer_id(http_response, CUSTOMER_ID_SIZE);
	get_all_customer_devices(customer_id);

	free(http_response);
	free(customer_id);

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

#define PAGE_SIZE			"10"
#define PAGE				"0"
#define GET_DEVICE_INFO		"/api/customer/"

char *get_all_customer_devices(char *customer_id){
	char    response_buffer[BUFFSIZE];
	int 	fd;

	printf("%s\n", token);

	char get_device_info_http_request[500];
	bzero(get_device_info_http_request, sizeof(get_device_info_http_request));

	strcat(get_device_info_http_request, "GET ");
	strcat(get_device_info_http_request, GET_DEVICE_INFO);
	strcat(get_device_info_http_request, customer_id);
	strcat(get_device_info_http_request, "/deviceInfos?pageSize=");	
	strcat(get_device_info_http_request, PAGE_SIZE);	
	strcat(get_device_info_http_request, "&page=");
	strcat(get_device_info_http_request, PAGE);	
	strcat(get_device_info_http_request, " HTTP/1.1\r\nHost: ");
	strcat(get_device_info_http_request, HOST);
	strcat(get_device_info_http_request, "\r\nContent-Type: application/json");
    strcat(get_device_info_http_request, "\r\nX-Authorization: Bearer ");
	strcat(get_device_info_http_request, token);
	strcat(get_device_info_http_request, "\r\nConnection: close\r\n\r\n");

	printf("http_request: %s\n", get_device_info_http_request);
}