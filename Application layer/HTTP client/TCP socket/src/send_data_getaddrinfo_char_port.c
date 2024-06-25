#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     /* for write(), read() and close() */
#include <sys/socket.h> /* for socket(), connect()*/
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER  "localhost"
#define PORT    "8000"

char *form_http_request();

/*
    Create a TCP socket connection to host with port
    @host:
    @port:
    Return: socket_fd as the socket file descriptor
*/
int socket_connect(char *host, char *port){
    int socket_fd;
    struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
	};
    struct addrinfo *response;
    int err = getaddrinfo(host, port, &hints, &response);
    if(err != 0 || response == NULL) {
		printf("DNS lookup failed err=%d res=%p", err, response);
		exit(1);
	}

    struct sockaddr *addr;
    addr = response->ai_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(socket_fd == -1){
		perror("socket_fd");
		exit(1);
	}
	
	if(connect(socket_fd, addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);
	}

	return socket_fd;
}

int main(){
	int fd;
	int send_number = 0;//initilize to 0 to avoid garbage value

	while(1){
		fd = socket_connect(SERVER, PORT); 
		char send_string[50];
		sprintf(send_string, "%s, index: %d", "Hello, World !", send_number);
        char *http_request = form_http_request(send_string);

        if (write(fd, http_request, strlen(http_request)) < 0){
            close(fd);
            return 0;
        }
		
		shutdown(fd, SHUT_RDWR); 
		close(fd); 
		send_number += 1;
		sleep(1);
	}
	
	return 0;
}

char *form_http_request(char *send_string){
    char string_length[10];
	static char http_request[500];

    sprintf(string_length, "%ld", strlen(send_string));
    strcpy(http_request, "GET /");
    strcat(http_request, " HTTP/1.1\r\nHost:");
    strcat(http_request, SERVER);
    strcat(http_request, "Content-Type: application/x-www-form-urlencoded\r\nContent-Length: ");
    strcat(http_request, string_length);
    strcat(http_request, "\r\n\r\n");
    strcat(http_request, send_string);
    strcat(http_request, "\r\n");
    return http_request;
}
