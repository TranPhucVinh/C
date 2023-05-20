#include <stdio.h>
#include <string.h>
#include <netdb.h>

#define HOST "example.com"

int main(int argc, char *argv[]){
	struct hostent *hp;   

	if((hp = gethostbyname(HOST)) == NULL){
        printf("Fail to get host %s\n", HOST);
		return -1;
	} else {
        printf("Host name: %s\n", hp->h_name);
        printf("Alias: %s\n", hp->h_aliases[0]);
        if (hp->h_addrtype == AF_INET) printf("Host address type is AF_INET\n");
        printf("Address length: %d\n", hp->h_length);
        printf("%s\n", hp->h_addr_list[0]);
    }

	return 0;
}