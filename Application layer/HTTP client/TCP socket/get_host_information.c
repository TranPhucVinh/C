#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#define HOST "example.com"

int main(){
	struct hostent *hp;   
    struct sockaddr_in socket_address;

	if((hp = gethostbyname(HOST)) == NULL){
        printf("Fail to get host %s\n", HOST);
		return -1;
	}

    printf("Host name: %s\n", hp->h_name);// Host name: example.com
    printf("Alias: %s\n", hp->h_aliases[0]);// Alias: (null)
    if (hp->h_addrtype == AF_INET) printf("Host address type is AF_INET\n");// Host address type is AF_INET
    printf("Address length: %d\n", hp->h_length);// Address length: 4
    printf("%s\n", hp->h_addr_list[0]); //Garbage value

    //Parsing for IP address
    memcpy(&socket_address.sin_addr, hp->h_addr, hp->h_length);

    /*
        socket_address.sin_addr.s_addr returns the IP address IPv4 (32-bit)
        in byte order
        584628317 can be separated to 0x22 (34) 0xD8 (216) 0xB8 (184) and 0x5D (93)
        which results in IP: 93.184.216.34
    */
    printf("%d\n", socket_address.sin_addr.s_addr);// 584628317

    // Function inet_ntoa() can be used for that IP parsing
    printf("IP address: %s\n", inet_ntoa(socket_address.sin_addr));// IP address: 93.184.216.34

	return 0;
}
