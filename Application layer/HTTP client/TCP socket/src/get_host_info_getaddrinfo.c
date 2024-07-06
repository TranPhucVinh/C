#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#define HOST "example.com"
#define PORT "80"

int main(){
    struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
	};

    struct addrinfo *response;

    int err = getaddrinfo(HOST, PORT, &hints, &response);
    if(err != 0 || response == NULL) {
		printf("DNS lookup failed err=%d res=%p", err, response);
		return -1;
	}

    struct in_addr *addr;
    addr = &((struct sockaddr_in *)response->ai_addr)->sin_addr;
    printf("DNS lookup success, IP: %s\n", inet_ntoa(*addr));// 93.184.215.14
    
    freeaddrinfo(response);

	return 0;
}
