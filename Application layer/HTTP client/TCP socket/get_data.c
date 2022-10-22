#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //for write(), read() and close()
#include <sys/socket.h> //for listen(), send() and recv()
#include <netdb.h>

#define HOST "example.com"
#define PORT 80
#define PATH "/"

char *form_http_request();

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int sock;     

	if((hp = gethostbyname(host)) == NULL){
        printf("Fail to get host %s\n", HOST);
		return -1;
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
        recv_buf = (char*)malloc(1024);
        while(1)
        {
            read_size_chunk = read(fd, &recv_buf[index += read_size_chunk], 1024);
            if(read_size_chunk > 0)
            {
                recv_buf = realloc(recv_buf, index + read_size_chunk + 1024);
                printf("%s\n", recv_buf);
            }
            else
            {
                recv_buf = realloc(recv_buf, index + 1);
                recv_buf[index] = 0;
                break;
            }
        }

        shutdown(fd, SHUT_RDWR); 
        close(fd); 
        
        sleep(1);
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