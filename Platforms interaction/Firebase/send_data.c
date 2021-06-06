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
#include <openssl/ssl.h>

#define BUFFER_SIZE 1024

char HTTP_REQUEST[300] = "PUT /test.json HTTP/1.1\r\nHost: ";
char stringLength[10];
char sendValue[100] = "{'txt':'Hello, World !'}";

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
	char buffer[BUFFER_SIZE];

	if(argc < 3){
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(1); 
	}

	fd = socket_connect(argv[1], atoi(argv[2])); 

	sprintf(stringLength, "%ld", strlen(sendValue));

	strcat(HTTP_REQUEST, argv[1]);
	strcat(HTTP_REQUEST, "\r\nContent-Type: application/json");
	strcat(HTTP_REQUEST, "\r\nContent-Length: ");
	strcat(HTTP_REQUEST, stringLength);
	strcat(HTTP_REQUEST, "\r\n\r\n");
	strcat(HTTP_REQUEST, sendValue);
	strcat(HTTP_REQUEST, "\r\n");

	// initialize OpenSSL - do this once and stash ssl_ctx in a global var
	SSL_load_error_strings();
	SSL_library_init();
	SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());

	// create an SSL connection and attach it to the socket
	SSL *ssl_conn = SSL_new(ssl_ctx);
	SSL_set_fd(ssl_conn, fd);

	// perform the SSL/TLS handshake with the server - when on the
	// server side, this would use SSL_accept()
	int err = SSL_connect(ssl_conn);
	if (err != 1)
		abort(); // handle error

	SSL_write(ssl_conn, HTTP_REQUEST, strlen(HTTP_REQUEST));
	bzero(buffer, BUFFER_SIZE);

	/*
		SSL_read() which read the respone from HTTP server will also lengthen
		the time of the program so that the message will reach the server properly.
		Without SSL_read() the message isn't send properly.
	*/
	SSL_read(ssl_conn, buffer, BUFFER_SIZE -1);
	fprintf(stderr, "%s", buffer);

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	return 0;
}
