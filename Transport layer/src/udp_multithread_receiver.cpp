#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <errno.h>
#include <pthread.h>

#define BUFFSIZE 	256
#define PORT 		8000

int receiver_fd;
struct sockaddr_in src_addr;// Dummy src_addr;
socklen_t src_addr_len;

int udp_socket_param_init(){
    struct sockaddr_in receiver_addr;
    socklen_t len; 

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

void *read_udp_data(void *ptr){
    printf("Thread ID %lu\n", pthread_self());
    while(1){
        char buffer[BUFFSIZE];
        bzero(buffer, BUFFSIZE);//Delete buffer
        int bytes_received = recvfrom(receiver_fd, (char *)buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *) &src_addr, &src_addr_len);
        if (bytes_received > 0) {
            printf("%lu receives message: %s", pthread_self(), buffer);
            bzero(buffer, BUFFSIZE);         //Delete buffer
        } 
    }
}

#define TOTAL_THREADS 3

int main(int argc, char *argv[]){
    pthread_t thread_id[TOTAL_THREADS];

    receiver_fd = udp_socket_param_init();
    src_addr_len = sizeof(src_addr);

    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_create(&thread_id[i], NULL, read_udp_data, NULL);
    }

    while(1);// Infinite loop to keep the program running infinitely to wait for message from UDP sender
}
