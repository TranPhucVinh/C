#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <errno.h>

#define BUFFSIZE 	256
#define PORT 		8000

struct sockaddr_in receiver_addr; // Set global as receiver_addr is used by both udp_socket_param_init() and main()

int udp_socket_param_init(){
    //Create UDP socket receiver
    int receiver_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receiver_fd < 0){
        perror("receiver_fd\n");
    } else printf("Create UDP receiver socket successfully\n");
 
    receiver_addr.sin_family = PF_INET;                
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    receiver_addr.sin_port = htons(PORT);      

    //Bind to the local address
    if (bind(receiver_fd, (struct sockaddr *) &receiver_addr, sizeof(receiver_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start UDP socket receiver successfully through binding\n");

    return receiver_fd;
}

int main(int argc, char *argv[]){
    int receiver_fd = udp_socket_param_init();
    socklen_t src_addr_len = sizeof(receiver_addr);  //len is value/result

    while(1){
        char buffer[BUFFSIZE];
        bzero(buffer, BUFFSIZE); // Delete buffer
        int bytes_received = recvfrom(receiver_fd, (char *)buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *) &receiver_addr, &src_addr_len);
        if (bytes_received > 0) {
            printf("Message from UDP sender: %s\n", buffer);
            bzero(buffer, BUFFSIZE);         //Delete buffer
        } 
    }
}
