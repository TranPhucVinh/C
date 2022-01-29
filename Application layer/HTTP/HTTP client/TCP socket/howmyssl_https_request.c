#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <openssl/ssl.h>

#define HOST "howsmyssl.com"
#define PATH "https://www.howsmyssl.com/a/check" //for howsmyssl.com, path can't be /a/check   
#define PORT 443   
#define BUFFER_SIZE 4000

char https_request[500];

int socket_connect(const char *host, in_port_t port){
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

	fd = socket_connect(HOST, PORT); 

    bzero(https_request, sizeof(https_request));

    strcat(https_request, "GET ");
	strcat(https_request, PATH);
    strcat(https_request, " HTTP/1.1\r\n");
    strcat(https_request, "Host: ");
    strcat(https_request, HOST);
	strcat(https_request, "\r\nConnection: close\r\n\r\n");

    printf("%s\n", https_request);

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

	SSL_write(ssl_conn, https_request, strlen(https_request));
	bzero(buffer, BUFFER_SIZE);
	
	while(SSL_read(ssl_conn, buffer, BUFFER_SIZE -1) != 0){
		fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	return 0;
}