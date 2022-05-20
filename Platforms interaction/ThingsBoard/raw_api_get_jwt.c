#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include "cJSON.h"

#define HOST        "thingsboard.sysats.tech"
#define PORT        80
#define PATH        "/api/auth/login"

#define USER        "tranphucvinh96@gmail.com"
#define PASSWORD    "iotdev_admin"

#define TOKEN_SIZE			600
#define REFRESH_TOKEN_SIZE	500 

char *form_jwt_http_request();
char *form_login_json_string(char *user, char *password);
void get_jwt(char *_token, char *_refreshToken);
int  socket_connect(char *host, in_port_t port);

char token[TOKEN_SIZE], refreshToken[REFRESH_TOKEN_SIZE];

int main(int argc, char *argv[]){
	bzero(token, TOKEN_SIZE);
	bzero(refreshToken, REFRESH_TOKEN_SIZE);

	get_jwt(token, refreshToken);
	printf("token: %s\n", token);
	printf("refreshToken: %s\n", refreshToken);
	return 0;
}

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int sock;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
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

void get_jwt(char *_token, char *_refreshToken){
	const 	cJSON *token, *refreshToken;
	int 	fd;
   
	fd = socket_connect(HOST, PORT);
	char *http_request = form_jwt_http_request();
	// printf("DEBUG: %s\n", http_request);
	write(fd, http_request, strlen(http_request));

	/* Read HTTP response */
	char* recv_buf = NULL;
	int index = 0;
	int read_size_chunk = 0;
	recv_buf = (char*)malloc(1024);

	while(1)
    {
        read_size_chunk = read(fd, &recv_buf[index += read_size_chunk], 1024);
        if(read_size_chunk > 0)
        {
            recv_buf = realloc(recv_buf, index + read_size_chunk + 1024);
        }
        else
        {
            recv_buf = realloc(recv_buf, index + 1);
            recv_buf[index] = 0;
            break;
        }
    }

    // printf("DEBUG: %s\n", recv_buf);
	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	// response_buffer = HTTP response header + JWT as JSON type
	char* temp_json_parsed;
	strtok(recv_buf, "{");
	temp_json_parsed = strtok(NULL, "}");

	int jwt_json_size = strlen(temp_json_parsed) + 2;//2 for "{"" and "}"
	char jwt_json[jwt_json_size];
	bzero(jwt_json, jwt_json_size);

	strcat(jwt_json, "{");
	strcat(jwt_json, temp_json_parsed);
	strcat(jwt_json, "}");

	printf("DEBUG: %s\n", jwt_json);

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

char *form_login_json_string(char *user, char *password){
    cJSON *json = cJSON_CreateObject();
    cJSON *_user = NULL, *_password = NULL;

    if (json == NULL) return NULL;

    _user = cJSON_CreateString(user);
    if (_user == NULL) return NULL;

    _password = cJSON_CreateString(password);
    if (_password == NULL) return NULL;

    cJSON_AddItemToObject(json, "username", _user);
    cJSON_AddItemToObject(json, "password", _password);
    char *jsonString = cJSON_Print(json);//Form a JSON string with cJSON_Print()
    return jsonString;
}

char *form_jwt_http_request(){
	static char http_request[500];
    char data_length[11];
	char *login_json_string = form_login_json_string(USER, PASSWORD);

    sprintf(data_length, "%ld", strlen(login_json_string));

	bzero(http_request, sizeof(http_request));
	strcat(http_request, "POST ");
	strcat(http_request, PATH);
	strcat(http_request, " HTTP/1.1\r\nHost: ");
	strcat(http_request, HOST);
	strcat(http_request, "\r\nContent-Type: application/json");
    strcat(http_request, "\r\nContent-Length: ");
    strcat(http_request, data_length);
    strcat(http_request, "\r\n\r\n");
    strcat(http_request, login_json_string);

	return http_request;
}