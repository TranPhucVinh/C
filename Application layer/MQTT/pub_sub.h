#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MQTT_CONNECT 1
#define MQTT_CONNACK 2
#define MQTT_PUBLISH 3

#define FIX_HEADER_SIZE 2 // 1 byte (control packet) + 1 byte (remaining length)

// CONNECT and CONNACK
#define CONN_SIZE       1024
#define CONNACK_REMAIN_LEN  2
#define CONNECTION_ACCEPTED         0x0
#define UNACCEPT_PROTOCOL_VERSION   0x1
#define IDENTIFIER_REJECT           0x2
#define SERVER_UNAVAILABLE          0x3
#define WRONG_USERNAME_PASSWORD     0x4
#define UNAUTHORIZED                0x5

// PUBLISH
#define PUB_SIZE        1024
#define QoS_0           0xf9

typedef struct {
    uint8_t control_type; // MQTT Control Packet type
    uint8_t control_flag; // Flags specific to each MQTT Control Packet type
    int remaining_length;
} mqtt_fix_header_t;

typedef struct {
    uint8_t packet_identifier[2];
    union {
        uint8_t connect_flag_byte;
        struct {
            uint8_t rev:1; /* Unused */
            uint8_t clean_session:1;
            uint8_t will_flag:1;
            uint8_t will_qos:2;
            uint8_t will_retain:1;
            uint8_t password_flag:1;
            uint8_t username_flag:1;
        } connect_flag_bit;
    };
    uint16_t keep_alive;
    uint8_t *pub_topic_name;
} mqtt_var_header_t;

typedef struct {
    uint8_t *client_id;
    uint8_t *subscribe_topic;
    uint8_t *message;
    uint8_t *user_name;
    uint8_t *password;
    int message_size;
} mqtt_payload_t;

typedef struct {
    mqtt_fix_header_t fix_header;
    mqtt_var_header_t var_header;
    mqtt_payload_t payload;
} mqtt_packet_t;

void  send_connect_packet(int sockfd, char *client_id, int keep_alive_sec);
void  publish_message(int sockfd, char* topic, uint8_t *msg);
int   mqtt_broker_connect(const char* mqtt_broker, int mqtt_port);