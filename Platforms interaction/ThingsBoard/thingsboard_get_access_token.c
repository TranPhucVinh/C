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
#define TOTAL_DEVICE_ID		10

#define ACCESS_TOKEN		20

char token[TOKEN_SIZE], refreshToken[REFRESH_TOKEN_SIZE];
char *device_id_array[TOTAL_DEVICE_ID];

char *http_response = NULL;
char *get_customer_id(char *http_response, int customer_id_size);
char *get_all_customer_devices(char *customer_id);
int  get_device_id(char *json_string, char *field_name, char *device_id_array[TOTAL_DEVICE_ID]);
void get_access_token(char *device_id_array[TOTAL_DEVICE_ID], int total_devices);

int main(int argc, char *argv[]){
	server_side_api_param_init(HOST, PORT, LOGIN_PATH, USER, PASSWORD);

	bzero(token, TOKEN_SIZE);
	bzero(refreshToken, REFRESH_TOKEN_SIZE);

	get_jwt(token, refreshToken, BUFFSIZE);

	http_response = http_request_for_api_with_jwt(API, "GET", token, BUFFSIZE);

	char *customer_id;
	char *customer_devices_info = NULL, *customer_devices_json = NULL;

	customer_id = get_customer_id(http_response, CUSTOMER_ID_SIZE);
	customer_devices_info = get_all_customer_devices(customer_id);

	customer_devices_json = strstr(customer_devices_info, "{\"data\":");

	//Get all existed devices ID
	int total_devices = get_device_id(customer_devices_json, "data", device_id_array);

	get_access_token(device_id_array, total_devices);

	free(http_response);
	free(customer_id);
	free(customer_devices_info);

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

//return total devices that a customer have
int  get_device_id(char *json_string, char *field_name, char *device_id_array[TOTAL_DEVICE_ID]){
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
			cJSON *id_field = NULL, *device_id = NULL;
			id_field = cJSON_GetObjectItemCaseSensitive(cJSON_Parse(cJSON_Print(array_member)), "id");
			device_id = cJSON_GetObjectItemCaseSensitive(cJSON_Parse(cJSON_Print(id_field)), "id");

			char *device_id_string = cJSON_Print(device_id);

			//Remove " character from device_id_string at index 0 and index strlen(device_id_string)-1
			memmove(device_id_string, device_id_string+1, strlen(device_id_string));
			device_id_string[strlen(device_id_string)-1] = 0;
			
			device_id_array[index] = device_id_string;
			// printf("%s\n", device_id_string);
			index += 1;
		}
	} else printf("Fail");
	return index;
}

#define GET_ACCESS_TOKEN "/api/device/"

void get_access_token(char *device_id_array[TOTAL_DEVICE_ID], int total_devices){
	for (int index=0; index < total_devices; index++){
		char    *response_buffer;
		int 	fd;

		response_buffer = (char*) malloc(BUFFSIZE * sizeof(char));
		bzero(response_buffer, BUFFSIZE);

		char http_request[1024];//Must be big to store token
		bzero(http_request, sizeof(http_request));

		strcat(http_request, "GET ");
		strcat(http_request, GET_ACCESS_TOKEN);
		strcat(http_request, device_id_array[index]);
		strcat(http_request, "/credentials");	
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

		char* temp_json_parsed = NULL;
		temp_json_parsed = strstr(response_buffer, "credentialsId");

		// printf("%s\n", temp_json_parsed);

		int credentials_id_size = strlen(temp_json_parsed) + 1;//1 for "{"

		char *credentials_id = (char*) malloc (credentials_id_size * sizeof(char));
		bzero(credentials_id, credentials_id_size);

		strcat(credentials_id, "{\"");
		strcat(credentials_id, temp_json_parsed);
        
        //Remove the last 0 character
        credentials_id[credentials_id_size-1] = 0;

		cJSON *json_object = cJSON_Parse(credentials_id);
		if (json_object == NULL)
		{
			const char *error_ptr = cJSON_GetErrorPtr();
			if (error_ptr != NULL)
			{
				fprintf(stderr, "Error before: %s\n", error_ptr);
			}
		}

		char *access_token = (char*) malloc(ACCESS_TOKEN * sizeof(char));

		cJSON *credentials_id_object = cJSON_GetObjectItemCaseSensitive(json_object, "credentialsId");

		if (cJSON_IsString(credentials_id_object) && (credentials_id_object->valuestring != NULL))
		{
			strcpy(access_token, credentials_id_object->valuestring);
			printf("Access token %s\n", access_token);
		} else printf("Fail to get token");

        free(access_token);
        free(response_buffer);
        free(credentials_id);
	}
}
