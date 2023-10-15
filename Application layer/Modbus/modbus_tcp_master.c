#include <stdio.h>      
#include <sys/socket.h> /* for socket(), connect()*/
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <errno.h>

#define HOST "127.0.0.1"
#define PORT 8000

#define	PROTO_ID		        0x00
#define LENGTH			        6
#define SLAVE_ADDRESS          	0x01
#define HLD_REG_MSB    	        0x00 // MSB of holding register address to start reading 
#define HLD_REG_LSB    	        0x01 // LSB of holding register address to start reading 
#define NUM_OF_REG_MSB   	    0x00
#define NUM_OF_REG_LSB   	    0x01 

#define FUNCTION_CODE           0x03 //Read multiple holding registers
int socket_parameter_init(const char *host, int port);
void error(const char *msg);

int main(){
    int trans_id = 0x1234;//Transaction identifier, can be any number to be unique to be distinguished
    uint8_t trans_id_lsb = (uint8_t)trans_id;  //0x34, last byte
    uint8_t trans_id_msb = trans_id>>8;       //0x12; first byte

    int proto_id = 0x00;// Protocol ID
    uint8_t proto_id_lsb = (uint8_t)proto_id;  //0x34, last byte
    uint8_t proto_id_msb = proto_id>>8;       //0x12; first byte

    int length = 0x06;//6 bytes in length includes: Slave address (unit identifier), function code, HLD_REG_MSB, HLD_REG_LSB and data (2 bytes = NUM_OF_REG_MSB + NUM_OF_REG_LSB)
    uint8_t length_lsb = (uint8_t)length;  //0x34, last byte
    uint8_t length_msb = length>>8;       //0x12; first byte

    int sender_fd = socket_parameter_init(HOST, PORT);
        
    // Send Modbus TCP frame to server/slave
    uint8_t modbus_tcp_frame[] = {trans_id_msb, trans_id_lsb, proto_id_msb, proto_id_lsb, length_msb, length_lsb, SLAVE_ADDRESS, FUNCTION_CODE, HLD_REG_MSB, HLD_REG_LSB, NUM_OF_REG_MSB, NUM_OF_REG_LSB};

    int sz = write(sender_fd, modbus_tcp_frame, sizeof(modbus_tcp_frame)/sizeof(uint8_t));

    close(sender_fd); //Close socket
    return 0;
}

void error(const char *msg){
    perror(msg);
    exit(0);
}
 
int socket_parameter_init(const char *host, int port){
    int sender_fd;
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family      = PF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(host);          
    receiver_addr.sin_port        = htons(port);

    // Create TCP socket
    if ((sender_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("Fail to create socket\n");
        exit(0);
    } else printf("Create socket successfully\n");

    // Connect to server
    if (connect(sender_fd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0){
        if (errno == ECONNREFUSED) {
            printf("Server hasn't been started or server doesn't support connection\n");
        } else printf("Can't connect to server with error %d", errno);
        exit(0);
    } else printf("connect to server success\n");
    return sender_fd;
}