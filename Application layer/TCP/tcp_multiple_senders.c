#include <stdio.h>      
#include <sys/socket.h> /* for socket(), connect()*/
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <errno.h>

#define HOST "127.0.0.1"
#define PORT 8000

#define BUFFSIZE 256
int sockfd;
struct sockaddr_in receiver_addr;
char buffer[BUFFSIZE];

void error(const char *msg){
    perror(msg);
    exit(0);
}
 
void socket_parameter_init(){
    receiver_addr.sin_family      = PF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(HOST);          
    receiver_addr.sin_port        = htons(PORT);

    // Create TCP socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("Fail to create socket\n");
        exit(0);
    } else printf("Create socket successfully\n");

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr))<0){
        if (errno == ECONNREFUSED) {
            printf("Server hasn't been started or server doesn't support connection\n");
        } else printf("Can't connect to server with error %d", errno);
        exit(0);
    } else printf("connect to server success\n");
}

int main(){
    socket_parameter_init();
    
    // Send data
    while(1){
        printf("message: ");
        bzero(buffer, BUFFSIZE);
        fgets(buffer, BUFFSIZE, stdin);

        write(sockfd, buffer, BUFFSIZE);
    }

    close(sockfd); //Close socket
    return 0;
}
