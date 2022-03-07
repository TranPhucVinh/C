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
	char *customer_devices;

	customer_id = get_customer_id(http_response, CUSTOMER_ID_SIZE);
	customer_devices = get_all_customer_devices(customer_id);

	printf("customer_devices: %s", customer_devices);

	free(http_response);
	free(customer_id);
	free(customer_devices);

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
	char    *response_buffer;
	int 	fd;

	response_buffer = (char*) malloc(BUFFSIZE * sizeof(char));
	bzero(response_buffer, BUFFSIZE);

	char http_request[1024];//Must be big to store token
	bzero(http_request, sizeof(http_request));

	strcat(http_request, "GET ");
	strcat(http_request, GET_DEVICE_INFO);
	strcat(http_request, customer_id);
	strcat(http_request, "/deviceInfos?pageSize=");	
	strcat(http_request, PAGE_SIZE);	
	strcat(http_request, "&page=");
	strcat(http_request, PAGE);	
	strcat(http_request, " HTTP/1.1\r\nHost: ");
	strcat(http_request, HOST);
	strcat(http_request, "\r\nContent-Type: application/json");
    strcat(http_request, "\r\nX-Authorization: Bearer ");
	strcat(http_request, token);
	strcat(http_request, "\r\nConnection: close\r\n\r\n");

	fd 		= socket_connect();
	write(fd, http_request, strlen(http_request));

	//After reading all HTTP response from JWT (not until reaching BUFFSIZE character), break the while loop
	//Without break, the program will hang as read() will keep waiting for the coming bytes although there is no bytes left
	while(read(fd, response_buffer, BUFFSIZE) != 0) {
		break;
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	return response_buffer;
}