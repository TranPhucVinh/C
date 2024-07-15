#include "pub_sub.h"
#include "control_packet_setup.h"

#define MQTT_BROKER     "broker.emqx.io"
#define MQTT_PORT       1883
#define MQTT_TOPIC      "test/message"
#define MQTT_CLIENT_ID  "mqtt_client_id"
#define MQTT_PAYLOAD    "Hello, World from MQTT client"

#define BUFF_SIZE       1024

#define KEEP_ALIVE_SEC  10 // KEEP_ALIVE seconds

bool broker_connected = false;

void parse_mqtt_packet(uint8_t *buf, int packet_sz) {
    /* Fix header section */
    int index = 0;
    int multiplier = 1;
    uint8_t encoded_byte;
    int remain_length = 0;
    uint8_t control_type = (buf[index++] >> 4) & 0xFF;

    /* Decode remaining length field, section 2.2.3 Remaining Length */
    do {
        encoded_byte = buf[index++];
        remain_length += (encoded_byte & 0x7F) * multiplier;
        multiplier *= 128;
    } while((encoded_byte & 0x80) && index < FIX_HEADER_SIZE);

    switch (control_type) {
        case MQTT_CONNACK:
            {
                if (remain_length != CONNACK_REMAIN_LEN) {
                    printf("Invalid MQTT_CONNACK packet\n");
                    return;
                }
                // todo with byte 1
                index++;

                uint8_t ret_code = buf[index++];// CONNACK return code
                switch (ret_code) {
                    case CONNECTION_ACCEPTED:
                    {
                        printf("Connection Accepted\n");
                        broker_connected = true;
                        break;
                    }
                    case UNACCEPT_PROTOCOL_VERSION:
                    {
                        printf("Connection Refused, unacceptable protocol version\n");
                        return;
                    }
                    case IDENTIFIER_REJECT:
                    {
                        printf("Connection Refused, identifier rejected\n");
                        return;
                    }
                    case SERVER_UNAVAILABLE:
                    {
                        printf("Connection Refused, Server unavailable\n");
                        return;
                    }
                    case WRONG_USERNAME_PASSWORD:
                    {
                        printf("Connection Refused, bad user name or password\n");
                        return;
                    }
                    case UNAUTHORIZED:
                    {
                        printf("Connection Refused, unauthorized\n");
                        return;
                    }
                    default:
                    {
                        printf("Invalid rc code for MQTT_CONNACK: 0x%02X\n", ret_code);
                        return;    
                    }                        
                }
            }
            break;

        default:
            break;
    }
}

void *receive_handler(void *parg) {
    int socketfd = *(int*)parg;
    uint8_t receive_buffer[BUFF_SIZE];
    printf("Init received thread\n");
    while(1) {
        int received_size = read(socketfd, receive_buffer, BUFF_SIZE);
        if (received_size > 0) {
            parse_mqtt_packet(receive_buffer, received_size);
        }
    }
}

int main() {
    pthread_t received_thread_t;
    int sockfd = mqtt_broker_connect(MQTT_BROKER, MQTT_PORT);

    pthread_create(&received_thread_t, NULL, receive_handler, &sockfd);
    sleep(1);

    send_connect_packet(sockfd, MQTT_CLIENT_ID, KEEP_ALIVE_SEC);

    while(!broker_connected) {
        sleep(1);/* Wait for connect status */
    }
    sleep(3);

    publish_message(sockfd, MQTT_TOPIC, MQTT_PAYLOAD);

    close(sockfd);

    return 0;
}