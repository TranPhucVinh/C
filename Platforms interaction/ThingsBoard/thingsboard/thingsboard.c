#include "thingsboard.h"

char *_server_side_api_param_init(char *host, int port, char *login_path, char *user, char *password){
    _host = host;
    _port = port;
    _login_path = login_path;
    _user = user;
    _password = password;
}

int socket_connect(){
	struct hostent *hp;
	struct sockaddr_in addr;
	int sock;     

	if((hp = gethostbyname(_host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(_port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sock == -1){
		perror("setsockopt");
		exit(1);
	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);

	}
	return sock;
}

char *form_login_json_string(){
    cJSON *json = cJSON_CreateObject();
    cJSON *json_user = NULL, *json_password = NULL;

    if (json == NULL) return NULL;

    json_user = cJSON_CreateString(_user);
    if (json_user == NULL) return NULL;

    json_password = cJSON_CreateString(_password);
    if (json_password == NULL) return NULL;

    cJSON_AddItemToObject(json, "username", json_user);
    cJSON_AddItemToObject(json, "password", json_password);
    char *jsonString = cJSON_Print(json);//Form a JSON string with cJSON_Print()
    return jsonString;
}

char *form_jwt_http_request(){
	static char http_request[500];
    char data_length[11];
	char *login_json_string = form_login_json_string();

    sprintf(data_length, "%ld", strlen(login_json_string));

	bzero(http_request, sizeof(http_request));
	strcat(http_request, "POST ");
	strcat(http_request, _login_path);
	strcat(http_request, " HTTP/1.1\r\nHost: ");
	strcat(http_request, _host);
	strcat(http_request, "\r\nContent-Type: application/json");
    strcat(http_request, "\r\nContent-Length: ");
    strcat(http_request, data_length);
    strcat(http_request, "\r\n\r\n");
    strcat(http_request, login_json_string);

	return http_request;
}

char *form_http_request_for_api_with_jwt(char *api, char *_method, char *_token){
	static char http_request[500];

	bzero(http_request, sizeof(http_request));
	strcat(http_request, _method);
	strcat(http_request, " ");
	strcat(http_request, api);
	strcat(http_request, " HTTP/1.1\r\nHost: ");
	strcat(http_request, _host);
	strcat(http_request, "\r\nContent-Type: application/json");
    strcat(http_request, "\r\nX-Authorization: Bearer ");
	strcat(http_request, _token);
	strcat(http_request, "\r\nConnection: close\r\n\r\n");
	
	return http_request;
}

void get_jwt(char *_token, char *_refreshToken, int read_buffer_size){
	const 	cJSON *token, *refreshToken;
	char    response_buffer[read_buffer_size];
	int 	fd;
   
	fd = socket_connect(_host, _port);
	char *http_request = form_jwt_http_request();

	write(fd, http_request, strlen(http_request));

	//After reading all HTTP response from JWT (not until reaching BUFFSIZE character), break the while loop
	//Without break, the program will hang as read() will keep waiting for the coming bytes although there is no bytes left
	while(read(fd, response_buffer, read_buffer_size) != 0) {
		break;
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	//response_buffer = HTTP response header + JWT as JSON type
	char* temp_json_parsed;
	strtok(response_buffer, "{");
	temp_json_parsed = strtok(NULL, "}");

	int jwt_json_size = strlen(temp_json_parsed) + 2;//2 for "{"" and "}"
	char jwt_json[jwt_json_size];
	bzero(jwt_json, jwt_json_size);

	strcat(jwt_json, "{");
	strcat(jwt_json, temp_json_parsed);
	strcat(jwt_json, "}");

	cJSON *jwt = cJSON_Parse(jwt_json);
	if (jwt == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
	}

	token = cJSON_GetObjectItemCaseSensitive(jwt, "token");
	if (cJSON_IsString(token) && (token->valuestring != NULL))
	{
		/*
			strcpy() for char token[TOKEN_SIZE]
			not _token = token->valuestring -> This will return NULL
		*/
		strcpy(_token, token->valuestring);
	} else printf("Fail to get token");

	refreshToken = cJSON_GetObjectItemCaseSensitive(jwt, "refreshToken");
	if (cJSON_IsString(refreshToken) && (refreshToken->valuestring != NULL))
	{
		/*
			strcpy() for refreshToken[REFRESH_TOKEN_SIZE]
			not refreshToken = refreshToken->valuestring -> This will return NULL
		*/
		strcpy(_refreshToken, refreshToken->valuestring);
	} else printf("Fail to get refreshToken");
}

char *http_request_for_api_with_jwt(char *api, char *method, char *_token, int read_buffer_size){
	int 	fd;
	char    *response_buffer;

	response_buffer = (char*) malloc(read_buffer_size * sizeof(char));
	bzero(response_buffer, read_buffer_size);
	
	fd 		= socket_connect(_host, _port);

	char *http_request = form_http_request_for_api_with_jwt(api, method, _token);

	write(fd, http_request, strlen(http_request));

	//After reading all HTTP response from JWT (not until reaching BUFFSIZE character), break the while loop
	//Without break, the program will hang as read() will keep waiting for the coming bytes although there is no bytes left
	while(read(fd, response_buffer, read_buffer_size) != 0) {
		break;
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	return response_buffer;
}