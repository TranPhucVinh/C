#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>

#define UDS_PATH "/tmp/ipc.socket"
#define RX_BUFF_SZ  1024 // UDS receiver buffer size

#define MAXPENDING 	1

int socket_parameter_init(char *uds_path);

int main() {
    struct sockaddr_un sender_addr;
    socklen_t sender_length = sizeof(sender_addr);

    int receiver_fd = socket_parameter_init(UDS_PATH);

    printf("UDS receiver is listening...\n");

    while (1) {
        char buffer[RX_BUFF_SZ] = {0};
        int sender_fd;
        
        if ((sender_fd = accept(receiver_fd, (struct sockaddr *)&sender_addr, &sender_length)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Connection established with UDS sender\n");

        ssize_t bytes_received;

        if ((bytes_received = read(sender_fd, buffer, RX_BUFF_SZ)) < 0) {
            perror("receive failed");
            exit(EXIT_FAILURE);
        }

        printf("Received message: %s\n", buffer);

        close(sender_fd);
    }

    return 0;
}

/*
   * Init UDS parameter
   * Create a Unix domain socket located in uds_path
*/
int socket_parameter_init(char *uds_path){
    int receiver_fd;
    struct sockaddr_un receiver_addr;

    /*
        Create UDS socket:
        * IPPROTO_IP is treated as a Dummy protocol. As UDS don't involve with IP, use this macro
    */ 
    if ((receiver_fd = socket(AF_UNIX, SOCK_STREAM, IPPROTO_IP)) < 0) {
        perror("UDS creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sun_family = AF_UNIX;
    strncpy(receiver_addr.sun_path, uds_path, sizeof(receiver_addr.sun_path));
    
    unlink(uds_path);// Remove the old UDS with path uds_path every time calling socket_parameter_init() 

    // Bind the socket to the specified path
    if (bind(receiver_fd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(receiver_fd, MAXPENDING) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    return receiver_fd;
}