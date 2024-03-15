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

#include <iostream>
#include <algorithm>
#include <vector>

#define BUFFSIZE 	256
#define PORT 		8000

#define TOTAL_THREADS           3
#define THREAD_BARRIERS_NUMBER  4
#define PTHREAD_BARRIER_ATTR    NULL // pthread barrier attribute

pthread_barrier_t barrier;

int receiver_fd;
struct sockaddr_in src_addr;// Dummy src_addr;
socklen_t src_addr_len;

using namespace std;

vector<string> recv_buffer;

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
            if (buffer[0] == 's'){
                recv_buffer.push_back(&buffer[2]);
                bzero(buffer, BUFFSIZE);         // Clean buffer
                pthread_barrier_wait(&barrier);
            }
        } 
    }
}

int main(int argc, char *argv[]){
    pthread_t thread_id[TOTAL_THREADS];

    receiver_fd = udp_socket_param_init();
    src_addr_len = sizeof(src_addr);

    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_create(&thread_id[i], NULL, read_udp_data, NULL);
    }

    pthread_barrier_init(&barrier, PTHREAD_BARRIER_ATTR, THREAD_BARRIERS_NUMBER);

    pthread_barrier_wait(&barrier);// This makes main() to wait for its TOTAL_THREADS to receive the data from UDP client
            
    // Must have while(1) to wait for the UDP sender to send data
    while (1){
        std::sort(recv_buffer.begin(), recv_buffer.end());

        for (int i = 0; i < recv_buffer.size(); i++){
            cout << recv_buffer[i];
        }

        cout << endl;
        break;
    }

    pthread_barrier_destroy(&barrier);
}