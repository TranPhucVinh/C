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
void error(const char *msg);

int main(){
   int sender_fd;
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family      = PF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(HOST);          
    receiver_addr.sin_port        = htons(PORT);

    // Create UDP socket
    if ((sender_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        printf("Fail to create UDP socket\n");
        exit(0);
    } else printf("Create UDP socket successfully\n");

    // There is no need to connect to the UDP receiver (by connect()) before sending message

    // As using sendto() which requires sockaddr_in as parameter, a socket param init function, like socket_parameter_init() in TCP, can't be used.
    // It's better to handle this encapsulation in UDP by using OOP.
    while(1){
        char buffer[BUFFSIZE];
        printf("message: ");
        bzero(buffer, BUFFSIZE);
        fgets(buffer, BUFFSIZE, stdin);
        sendto(sender_fd, buffer, BUFFSIZE, MSG_CONFIRM, (const struct sockaddr *) &receiver_addr, sizeof(receiver_addr)); 
    }
    return 0;
}

void error(const char *msg){
    perror(msg);
    exit(0);
}
