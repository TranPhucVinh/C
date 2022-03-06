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

#define BUFFSIZE        4096 //Size must be big to get all JWT

char    response_buffer[BUFFSIZE];

char *form_http_request();
char *form_json_string();

int  send_number = 0;

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

int main(int argc, char *argv[]){
	int fd;
   
	fd = socket_connect(HOST, PORT);
	char *http_request = form_http_request();
	printf("Request: %s\n", http_request);
	write(fd, http_request, strlen(http_request));

	//After reading all HTTP response from JWT (not until reaching BUFFSIZE character), break the while loop
	//Without break, the program will hang as read() will keep waiting for the coming bytes although there is no bytes left
	while(read(fd, response_buffer, BUFFSIZE) != 0) {
		break;
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	printf("%s", response_buffer);

	return 0;
}

char *form_json_string(){
    cJSON *json = cJSON_CreateObject();
    cJSON *user = NULL, *password = NULL;

    if (json == NULL) return NULL;

    user = cJSON_CreateString(USER);
    if (user == NULL) return NULL;

    password = cJSON_CreateString(PASSWORD);
    if (password == NULL) return NULL;

    cJSON_AddItemToObject(json, "username", user);
    cJSON_AddItemToObject(json, "password", password);
    char *jsonString = cJSON_Print(json);//Form a JSON string with cJSON_Print()
    return jsonString;
}

char *form_http_request(){
	static char http_request[500];
    char data_length[11];
    sprintf(data_length, "%ld", strlen(form_json_string()));

	bzero(http_request, sizeof(http_request));
	strcat(http_request, "POST ");
	strcat(http_request, PATH);
	strcat(http_request, " HTTP/1.1\r\nHost: ");
	strcat(http_request, HOST);
	strcat(http_request, "\r\nContent-Type: application/json");
    strcat(http_request, "\r\nContent-Length: ");
    strcat(http_request, data_length);
    strcat(http_request, "\r\n\r\n");
    strcat(http_request, form_json_string());

	return http_request;
}