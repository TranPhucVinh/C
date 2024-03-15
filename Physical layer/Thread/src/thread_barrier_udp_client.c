#include <stdio.h>      
#include <sys/socket.h> /* for socket(), connect()*/
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <errno.h>

#define HOST "127.0.0.1"
#define PORT 8000

void error(const char *msg);

int main(int argc, char** args){
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

    sendto(sender_fd, (const char *)args[1], strlen(args[1]), MSG_CONFIRM, (const struct sockaddr *) &receiver_addr, sizeof(receiver_addr)); 
    close(sender_fd);

    return 0;
}

void error(const char *msg){
    perror(msg);
    exit(0);
}