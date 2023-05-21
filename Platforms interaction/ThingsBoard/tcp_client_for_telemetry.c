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

#define READ_CHUNK      100

char    *form_http_request();

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in socket_address;
	int client_fd;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	memcpy(&socket_address.sin_addr, hp->h_addr, hp->h_length);
	socket_address.sin_port = htons(port);
	socket_address.sin_family = AF_INET;
	client_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(client_fd == -1){
		perror("client_fd");
		exit(1);
	}
	
	if(connect(client_fd, (struct sockaddr *)&socket_address, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);

	}
	return client_fd;
}

int main(int argc, char *argv[]){
    int  send_number = 0;
    char send_json[100];

    while (1){
        int client_fd = socket_connect(HOST, PORT);
        sprintf(send_json, "{'unix_tcp_client':%d}", send_number);        
        char *http_request = form_http_request(send_json);

        #ifdef DEBUG    
            printf("%s\n", http_request);
        #endif

        /*
            For network issue like WiFi not connected, write() 
            still write the HTTP request sucessfully
        */
        if (write(client_fd, http_request, strlen(http_request)) < 0){
            printf("Fail to send HTTP request\n");
            close(client_fd);
            return 0;
        } else {
            #ifdef DEBUG    
                /* Read HTTP response */
                char* recv_buf = NULL;
                int index = 0;
                int read_size_chunk = 0;
                recv_buf = (char*)malloc(READ_CHUNK * sizeof(char));
                while(1)
                {
                    read_size_chunk = read(client_fd, &recv_buf[index += read_size_chunk], READ_CHUNK);
                    if(read_size_chunk > 0) recv_buf = realloc(recv_buf, index + read_size_chunk + READ_CHUNK);
                    else
                    {
                        recv_buf = realloc(recv_buf, index + 1);
                        recv_buf[index] = 0;
                        break;
                    }
                }
                printf("%s\n", recv_buf);
            #endif
            send_number += 1;

            shutdown(client_fd, SHUT_RDWR); 
            close(client_fd); 
            sleep(3);
        }
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