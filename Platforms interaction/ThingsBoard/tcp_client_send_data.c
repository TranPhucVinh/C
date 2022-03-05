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

#define HOST          "demo.thingsboard.io"
#define PORT          80
#define TOKEN         "ky9YeJlntAnb3MzqqEYz"

char *form_http_request();
char *form_json_string();

int  send_number = 0;

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     

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
    char send_value[100];
    char https_request[500];
   
    while (1){
        sprintf(send_value, "{'esp-idf-number':%d}", send_number);
        fd = socket_connect(HOST, PORT);
        char *http_request = form_http_request(send_value);
        printf("%s\n", http_request);
        write(fd, http_request, strlen(http_request)); // write(fd, char[]*, len);  
        shutdown(fd, SHUT_RDWR); 
        close(fd); 
        send_number += 1;
        sleep(1);
    }
	return 0;
}

char *form_http_request(char *data){
	static char http_request[500];
    char string_length[11];
    sprintf(string_length, "%ld", strlen(data));

    bzero(http_request, sizeof(http_request));
    strcat(http_request, "POST /api/v1/");
    strcat(http_request, TOKEN);
    strcat(http_request, "/telemetry HTTP/1.1\r\n");
    strcat(http_request, "Host: ");
    strcat(http_request, HOST);
    strcat(http_request, "\r\n");
    strcat(http_request, "Content-Type: application/json\r\n");
    strcat(http_request, "Content-Length: ");
    strcat(http_request, string_length);
    strcat(http_request, "\r\n\r\n");
    strcat(http_request, data);

	return http_request;
}