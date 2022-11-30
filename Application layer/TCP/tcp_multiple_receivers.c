#include <stdio.h>      
#include <sys/socket.h> /* for socket(), connect()*/
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <errno.h>

#define HOST "127.0.0.1"
#define PORT 8000

#define BUFFSIZE 100

/*
    New Receiver Connected: Flag to inform TCP sender that TCP receiver 
    has connected and is ready to receive data from TCP sender
*/
#define NRC         "NRC"

int sockfd;
struct sockaddr_in sender_addr;
char buffer[BUFFSIZE];

void error(const char *msg){
    perror(msg);
    exit(0);
}
 
void socket_parameter_init(){
    sender_addr.sin_family      = PF_INET;
    sender_addr.sin_addr.s_addr = inet_addr(HOST);          
    sender_addr.sin_port        = htons(PORT);

    // Create TCP socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("Fail to create socket\n");
        exit(0);
    } else printf("Create socket successfully\n");

    // Connect to TCP sender
    if (connect(sockfd, (struct sockaddr *)&sender_addr, sizeof(sender_addr))<0){
        if (errno == ECONNREFUSED) {
            printf("TCP sender hasn't been started or TCP sender doesn't support connection\n");
        } else printf("Can't connect to TCP sender with error %d", errno);
        exit(0);
    } else printf("connect to TCP sender successfully\n");
}

int main(){
    socket_parameter_init();
    //Send NRC flag to TCP sender to confirm it's ready to receive message
    if (write(sockfd, NRC, sizeof(NRC)) == sizeof(NRC)){
        while(1){
            int bytes_received = read(sockfd, buffer, BUFFSIZE);
            if (bytes_received > 0) {
                printf("Message from TCP sender: %s\n", buffer);
            } 
        }
    }
    close(sockfd); //Close socket
    return 0;
}