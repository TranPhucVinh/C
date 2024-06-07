# Send data to Google drive

```c
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

#define HOST            "script.google.com"
#define SCRIPT_ID       "AKfycby2CHiFSrC4tPpgKx1dscjO-wqM4zy0Px9X5OI3LPjqufQ4xNWdxiCC5U2oqniXrlBc"
#define PORT            443   
#define SEND_DATA       "id="

#define BUFFER_SIZE 1024

void delaySeconds(long seconds);
char *form_http_request(char *data);
char https_request[500];

int sendNumber = 0;

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
    while (1){
        int fd;
        char buffer[BUFFER_SIZE];

        fd = socket_connect(HOST, PORT); 

        bzero(https_request, sizeof(https_request));

        char sendValue[4];
        sprintf(sendValue, "%d", sendNumber);
        strcpy(https_request, form_http_request(sendValue));

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

        SSL_write(ssl_conn, https_request, strlen(https_request)); // write(fd, char[]*, len);  
        bzero(buffer, BUFFER_SIZE);
        
        while(SSL_read(ssl_conn, buffer, BUFFER_SIZE -1) != 0){
            fprintf(stderr, "%s", buffer);
            bzero(buffer, BUFFER_SIZE);
        }

        shutdown(fd, SHUT_RDWR); 
        close(fd); 

        sendNumber += 1;
        delaySeconds(1);
    }

	return 0;
}

void delaySeconds(long seconds){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long totalSecond = 0;
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}

char *form_http_request(char *data){
    static char http_request[500];
    char webURL[200];

    bzero(webURL, sizeof(webURL));
    bzero(http_request, sizeof(http_request));
    strcat(webURL, "/macros/s/");
    strcat(webURL, SCRIPT_ID);
    strcat(webURL, "/exec?");
    strcat(http_request, "GET ");
    strcat(http_request, webURL);
    strcat(http_request, SEND_DATA);
    strcat(http_request, data);
    strcat(http_request, " HTTP/1.0\r\n");
    strcat(http_request, "Host: ");
    strcat(http_request, HOST);
    strcat(http_request,"\r\nUser-Agent: esp-idf/1.0 esp32\r\n\r\n");

	return http_request;
}
```
