#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     /* for write(), read() and close() */
#include <sys/socket.h> /* for socket(), connect()*/
#include <netdb.h>

#define HOST "example.com"
#define PORT 80
#define PATH "/"

#define READ_CHUNK  100

char *form_http_request();

/*
    Create a TCP socket connection to host with port
    @host:
    @port:
    Return: socket_fd as the socket file descriptor
*/
int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in socket_address;
	int socket_fd;     

	if((hp = gethostbyname(host)) == NULL){
        printf("Fail to get host %s\n", HOST);
		return -1;
	}
    memcpy(&socket_address.sin_addr, hp->h_addr, hp->h_length);
	socket_address.sin_port = htons(port);
	socket_address.sin_family = AF_INET;
	socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(socket_fd == -1){
		perror("socket_fd");
		exit(1);
	}
	
	if(connect(socket_fd, (struct sockaddr *)&socket_address, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);
	}

	return socket_fd;
}

int main(int argc, char *argv[]){
	int fd;

    while (1){
        fd = socket_connect(HOST, PORT); 
        char *http_request = form_http_request();
        printf("%s\n", http_request);

        if (write(fd, http_request, strlen(http_request)) < 0){
            close(fd);
            return 0;
        }

        /* Read HTTP response */
        char* recv_buf = NULL;
        int index = 0;
        int read_size_chunk = 0;
        recv_buf = (char*)malloc(READ_CHUNK);
        while(1)
        {
            read_size_chunk = read(fd, &recv_buf[index += read_size_chunk], READ_CHUNK);
            if(read_size_chunk > 0)
            {
                recv_buf = realloc(recv_buf, index + read_size_chunk + READ_CHUNK);
            }
            else
            {
                recv_buf = realloc(recv_buf, index + 1);
                recv_buf[index] = 0;
                break;
            }
        }
        printf("%s\n", recv_buf);
        shutdown(fd, SHUT_RDWR); 
        close(fd); 
        
        sleep(5);
    }
	return 0;
}

char *form_http_request(){
	static char http_request[500];

	bzero(http_request, sizeof(http_request));
	strcat(http_request, "GET ");
	strcat(http_request, PATH);
	strcat(http_request, " HTTP/1.0\r\nHost: ");
	strcat(http_request, HOST);
	strcat(http_request, "\r\nConnection: close\r\n\r\n");

	return http_request;
}