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

#define DEBUG
#define HOST          	"ec2-18-142-177-27.ap-southeast-1.compute.amazonaws.com"
#define PORT          	9090
#define TOKEN         	"47DF5DqQgOvw2J9jSlKK"
#define BUFFSIZE        256

char    response_buffer[BUFFSIZE];

char *form_http_request();

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
	int client_fd;
    char send_json[100];
    
    client_fd = socket_connect(HOST, PORT);

    while (1){
        sprintf(send_json, "{'unix_tcp_client':%d}", send_number);
        
        char *http_request = form_http_request(send_json);

        #ifdef DEBUG    
            printf("%s\n", http_request);
        #endif

        /*
            For network error like WiFi not connected, write() 
            still write the HTTP request sucessfully with
            wsz = strlen(http_request)
        */
        int wsz = write(client_fd, http_request, strlen(http_request));//wsz: write size
        
        #ifdef DEBUG    
            while(read(client_fd, response_buffer, BUFFSIZE - 1) != 0){
                fprintf(stderr, "%s\n", response_buffer);
                bzero(response_buffer, BUFFSIZE);
                break;
            }
        #endif

        if (wsz == strlen(http_request)) send_number += 1;
        else printf("Failt to send HTTP request\n");
        sleep(3);
    }
    shutdown(client_fd, SHUT_RDWR); 
    close(client_fd); 
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