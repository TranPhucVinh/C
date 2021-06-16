### Example 1

Send data to Blynk ``Value Display``

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
#include <sys/time.h>

#define WEB_SERVER  "blynk-cloud.com"
#define WEB_PORT    "80"

#define BLYNK_TOKEN "rYt4dTj5QqvSNFRZeS_ccmAm13Dcx-DX"
#define BLYNK_PIN   "V1"
#define BUFFER_SIZE 1024

void delaySeconds(long seconds);

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
	int sendNumber = 0;//initilize to 0 to avoid garbage value
	char buffer[BUFFER_SIZE];

	while(1){
		fd = socket_connect(WEB_SERVER, atoi(WEB_PORT)); 
		char sendString[50];
		char http_request[500] = "GET /";

		sprintf(sendString, "%s=%d", "?value", sendNumber);
        
		strcat(http_request, BLYNK_TOKEN);
        strcat(http_request, "/update/");
        strcat(http_request, BLYNK_PIN);
        strcat(http_request, sendString);
        strcat(http_request, " HTTP/1.1\r\nHost:");
        strcat(http_request, WEB_SERVER);
        strcat(http_request, "\r\nConnection: close\r\n\r\n");

		printf("request: %s\n", http_request);

		write(fd, http_request, sizeof(http_request));
		bzero(buffer, BUFFER_SIZE);
		
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
	long totalSecond = 0;//initilize to 0 to avoid garbage value
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}
```