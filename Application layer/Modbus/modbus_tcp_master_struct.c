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
#define LENGTH			        0x06
#define SLAVE_ADDRESS          	0x01
#define HLD_REG_MSB    	        0x00 // MSB of holding register address to start reading 
#define HLD_REG_LSB    	        0x01 // LSB of holding register address to start reading 
#define NUM_OF_REG_MSB   	    0x00
#define NUM_OF_REG_LSB   	    0x01 
#define FUNCTION_CODE           0x03 //Read multiple holding registers

int socket_parameter_init(const char *host, int port);

struct modbus_slave {
    uint8_t trans_id_msb;
    uint8_t trans_id_lsb;
    uint8_t proto_id_msb;
    uint8_t proto_id_lsb;
    uint8_t length_msb;
    uint8_t length_lsb;    
    uint8_t slave_address;
    uint8_t function_code;
    uint8_t hld_reg_msb;
    uint8_t hld_reg_lsb;
    uint8_t num_of_reg_msb;
    uint8_t num_of_reg_lsb;
} __attribute__((packed)); // Ensure no padding in struct;

int main(){
    struct modbus_slave slave;

    uint16_t trans_id = 0x1234; //Transaction identifier, can be any number to be unique to be distinguished
    slave.trans_id_msb = (uint8_t)(trans_id >> 8);       //0x12; first byte
    slave.trans_id_lsb = (uint8_t)(trans_id & 0xFF);  //0x34, last byte

    uint16_t proto_id = PROTO_ID;// Protocol ID
    slave.proto_id_msb = (uint8_t)(proto_id >> 8);       //0x12; first byte
    slave.proto_id_lsb = (uint8_t)(proto_id & 0xFF);  //0x34, last byte

    uint16_t length = LENGTH;//6 bytes in length includes: Slave address (unit identifier), function code, HLD_REG_MSB, HLD_REG_LSB and data (2 bytes = NUM_OF_REG_MSB + NUM_OF_REG_LSB)
    slave.length_msb = (uint8_t)(length >> 8);       //0x12; first byte
    slave.length_lsb = (uint8_t)(length & 0xFF);  //0x34, last byte

    slave.slave_address = SLAVE_ADDRESS;
    slave.function_code = FUNCTION_CODE;
    slave.hld_reg_msb   = HLD_REG_MSB;
    slave.hld_reg_lsb   = HLD_REG_LSB;

    slave.num_of_reg_msb   = NUM_OF_REG_MSB;
    slave.num_of_reg_lsb   = NUM_OF_REG_LSB;

    // print_frame(&slave);
    int sender_fd = socket_parameter_init(HOST, PORT);
        
    // Send Modbus TCP frame to server/slave
    int sz = write(sender_fd, &slave, sizeof(slave));

    close(sender_fd); //Close socket
    return 0;
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
