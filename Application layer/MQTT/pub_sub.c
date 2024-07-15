#include "pub_sub.h"
#include "control_packet_setup.h"

/*
    After a Network Connection is established by a Client to a Server, the first 
    Packet sent from the Client to the Server MUST be a CONNECT Packet
*/
void send_connect_packet(int sockfd, char *client_id, int keep_alive_sec) {
    uint8_t connect_packet[CONN_SIZE];// MQTT Control packet CONNECT
    mqtt_packet_t mqtt_packet;
    memset(&mqtt_packet, 0, sizeof(mqtt_packet_t));

    mqtt_packet.fix_header.control_type = MQTT_CONNECT;    

    /* Form variable header */
    /* We form variable header first from FIX_HEADER_SIZE since the fix header size is determined later */
    int index = FIX_HEADER_SIZE;
    mqtt_packet.var_header.connect_flag_bit.clean_session = 1;// 3.1.2.3 Connect Flags for MQTT_CONNECT
    mqtt_packet.var_header.keep_alive = keep_alive_sec;
    int var_header_sz = form_variable_header(&connect_packet[index], MQTT_CONNECT, mqtt_packet.var_header);
    index += var_header_sz;

    /* Form payload */
    mqtt_packet.payload.client_id = client_id;
    int payload_sz = form_payload(&connect_packet[index], mqtt_packet.payload);
    index += payload_sz;

    uint8_t fix_header[FIX_HEADER_SIZE];

    // Total length (packet length) of MQTT Control packet CONNECT: 1 (control type 1 byte = MQTT_CONNECT) + payload_sz + var_header_sz
    mqtt_packet.fix_header.remaining_length = payload_sz + var_header_sz;
    int fix_header_sz = form_fix_header(fix_header, mqtt_packet.fix_header);

    /* we need to place the fix header size in the correct place in the temp buffer */
    /*
        As index is initially FIX_HEADER_SIZE, 0 to FIX_HEADER_SIZE-1 is allocated for fix_header 
        Suppose FIX_HEADER_SIZE is 5 (1 for MQTT control type and flag) and 4 for remaining_length (its max value).
        If the fix header size is actually 3 with 2 bytes for remaining_length, form_fix_header() returns 3.

        In order to make a contiguous range of connect_packet, connect_packet must start at index 2, 
        with index [2 3 4] is corresponded to [0 1 2] in fix_header[FIX_HEADER_SIZE].
        So that's why we need: start_packet_index = FIX_HEADER_SIZE - fix_header_sz
    */ 
    int start_packet_index = FIX_HEADER_SIZE - fix_header_sz;
    memcpy(&connect_packet[start_packet_index], fix_header, fix_header_sz);

    printf("Send connect packet\n");
    if (write(sockfd, &connect_packet[start_packet_index], index - start_packet_index) < 0){
        perror("Send failed");
        return;
    }
}

void publish_message(int sockfd, char* topic, uint8_t *msg) {
    uint8_t publish_packet[PUB_SIZE];
    mqtt_packet_t mqtt_packet;
    memset(&mqtt_packet, 0, sizeof(mqtt_packet_t));
    uint8_t topic_sz = strlen(topic);

    mqtt_packet.fix_header.control_type = MQTT_PUBLISH;
    mqtt_packet.var_header.pub_topic_name = topic;

    mqtt_packet.payload.message = msg;
    mqtt_packet.payload.message_size = strlen(msg);

    /* We form variable header first from FIX_HEADER_SIZE since the fix header size is determined later */
    int index = FIX_HEADER_SIZE;
    int var_header_sz = form_variable_header(&publish_packet[index], MQTT_PUBLISH, mqtt_packet.var_header);
    index += var_header_sz;

    /* Form payload */
    int payload_sz = form_payload(&publish_packet[index], mqtt_packet.payload);
    index += payload_sz;

    uint8_t fix_header[FIX_HEADER_SIZE];
    mqtt_packet.fix_header.remaining_length = payload_sz + var_header_sz;
    int fix_header_sz = form_fix_header(fix_header, mqtt_packet.fix_header);
    /* we need to place the fix header size in the correct place in the temp buffer */
    int start_packet_index = FIX_HEADER_SIZE - fix_header_sz;
    memcpy(&publish_packet[start_packet_index], fix_header, fix_header_sz);

    printf("publish packet with topic: %s | message: %s\n", topic, msg);
    
    if (write(sockfd, &publish_packet[start_packet_index], index - start_packet_index) < 0){
        perror("Send failed");
        return;
    }
}

int mqtt_broker_connect(const char* mqtt_broker, int mqtt_port) {
    int sockfd;
    struct sockaddr_in serv_addr;

    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    if (getaddrinfo(mqtt_broker, NULL, &hints, &res) != 0) {
        return -1;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }
        ((struct sockaddr_in *)p->ai_addr)->sin_port = htons(mqtt_port);
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }

        break; // If we get here, we have successfully connected
    }
    if (p == NULL) {
        printf("Fail to get site info\n");
        return -1;
    }

    return sockfd;
}
