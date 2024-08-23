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

#define SERVER  "localhost"
#define PORT    8000

char *form_http_request();

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int socket_fd;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(socket_fd == -1){
		perror("socket_fd");
		exit(1);
	}
	
	if(connect(socket_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);
	}
	return socket_fd;
}

int main(int argc, char *argv[]){
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
