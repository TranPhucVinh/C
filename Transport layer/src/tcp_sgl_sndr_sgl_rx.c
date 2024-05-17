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

int socket_parameter_init(char *host, int port);

int main(){
    int sender_fd = socket_parameter_init(HOST, PORT);
    
    // Send data
    while(1){
        char buffer[BUFFSIZE];
        printf("message: ");
        bzero(buffer, BUFFSIZE);
        fgets(buffer, BUFFSIZE, stdin);

        write(sender_fd, buffer, BUFFSIZE);
    }

    close(sender_fd); //Close socket
    return 0;
}
 
int socket_parameter_init(char *host, int port){
    int sender_fd;
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family      = PF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(host);          
    receiver_addr.sin_port        = htons(port);

    // Create TCP socket
    if ((sender_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("Fail to create socket\n");
        exit(0);
    } else printf("Create TCP socket successfully\n");

    // Connect to the TCP receiver to send data to it in later steps
    if (connect(sender_fd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0){
        if (errno == ECONNREFUSED) {
            printf("TCP receiver hasn't been started or it doesn't support connection\n");
        } else printf("Can't connect to TCP receiver with error %d", errno);
        exit(0);
    } else printf("connect to TCP receiver successfully\n");
    return sender_fd;
}
