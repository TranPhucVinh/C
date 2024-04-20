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
void error(const char *msg);

int main(){
    int server_fd = socket_parameter_init(HOST, PORT);
    
    // Send data
    while(1){
        char buffer[BUFFSIZE];
        bzero(buffer, BUFFSIZE);// Delete buffer
        int bytes_received = read(server_fd, buffer, BUFFSIZE);
        if (bytes_received > 0) {
            printf("Message from TCP server: %s\n", buffer);
            bzero(buffer, BUFFSIZE);// Delete buffer
        } 
        else {
            printf("TCP server has disconnected. Stop TCP client, too\n");
            close(server_fd); 
            exit(0);
        }
    }
    return 0;
}

void error(const char *msg){
    perror(msg);
    exit(0);
}
 
int socket_parameter_init(char *host, int port){
    int server_fd;
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family      = PF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(host);          
    receiver_addr.sin_port        = htons(port);

    // Create TCP socket
    if ((server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("Fail to create socket\n");
        exit(0);
    } else printf("Create TCP socket successfully\n");

    // Connect to server
    if (connect(server_fd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0){
        if (errno == ECONNREFUSED) {
            printf("TCP server hasn't been started or server doesn't support connection\n");
        } else printf("Can't connect to TCP server with error %d", errno);
        exit(0);
    } else printf("connect to TCP server successfully\n");
    return server_fd;
}