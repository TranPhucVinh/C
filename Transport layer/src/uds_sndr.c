#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <errno.h>

#define UDS_PATH    "/tmp/ipc.socket"
#define MESSAGE     "Renamed to uds snder, uds receiver"

int socket_parameter_init(char *uds_path);

int main() {
    int sender_fd = socket_parameter_init(UDS_PATH);

    if (write(sender_fd, MESSAGE, sizeof(MESSAGE)) < 0) {
        perror("Fail to send message");
        exit(EXIT_FAILURE);
    }

    printf("Data sent successfully\n");

    close(sender_fd);
    return 0;
}

int socket_parameter_init(char *uds_path){
    int sender_fd;
    struct sockaddr_un receiver_addr;

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sun_family = AF_UNIX; // UNIX domain sockets 
    strncpy(receiver_addr.sun_path, uds_path, sizeof(receiver_addr.sun_path));

    /*
        Create UDS socket:
        * IPPROTO_IP is treated as a Dummy protocol. As UDS don't involve with IP, use this macro
    */ 
    if ((sender_fd = socket(AF_UNIX, SOCK_STREAM, IPPROTO_IP)) < 0){
        printf("Fail to create UDS socket\n");
        exit(0);
    } else printf("Create UDS socket successfully\n");

    // Connect to server
    if (connect(sender_fd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0){
        if (errno == ECONNREFUSED) {
            printf("UDS receiver hasn't been started or it doesn't support connection\n");
        } else printf("Can't connect to UDS receiver with error %d", errno);
        exit(0);
    } else printf("Connect to UDS receiver successfully\n");
    return sender_fd;
}