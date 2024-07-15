#include "control_packet_setup.h"

int form_fix_header(uint8_t *mqtt_packet_buf, mqtt_fix_header_t fix_header_s) {
    int index = 0;
    int remaining_length = fix_header_s.remaining_length;
    if (mqtt_packet_buf == NULL) {
        return -1;
    }
    switch (fix_header_s.control_type) {
        case MQTT_CONNECT:
            mqtt_packet_buf[index++] = (fix_header_s.control_type << 4) & 0xF0; /* table 2.2 flag bits */
            break;

        case MQTT_PUBLISH:
            /* Section 3.3 PUBLISH – Publish message */
            /* DUP flag and RETAIN are don't care */ 
            mqtt_packet_buf[index++] = ((fix_header_s.control_type << 4) & 0xF0) | (fix_header_s.control_flag & 0x0F & QoS_0);
            break;

        default:
            break;
    }

    do { /* Algorithm at 2.2.3 Remaining Length for encoding */
        uint8_t encode_byte = remaining_length%128;
        remaining_length = remaining_length/128;
        if (remaining_length > 0) {
            mqtt_packet_buf[index++] = encode_byte | 0x80;
        } else {
            mqtt_packet_buf[index++] = encode_byte;
        }
    } while (remaining_length > 0);

    return index;
}

/*
    Return the current as the variable_header_size
*/
int form_variable_header(uint8_t *mqtt_packet_buf, uint8_t control_type, mqtt_var_header_t var_header_s) {
    int index = 0;
    if (mqtt_packet_buf == NULL) {
        return -1;
    }
    switch (control_type) {
        case MQTT_CONNECT:
            {
                /* Section 3.1.2.1 Protocol Name */
                mqtt_packet_buf[index++] = 0x00;// byte 1 (i.e byte at index 0 in mqtt_packet_buf)
                mqtt_packet_buf[index++] = 0x04; // byte 2
                sprintf(&mqtt_packet_buf[index], "%s", "MQTT"); // byte 3 - 6
                index +=4;

                mqtt_packet_buf[index++] = 0x04; /* Section 3.1.2.2 Protocol Level - byte 7 */
                mqtt_packet_buf[index++] = var_header_s.connect_flag_byte; /* Section 3.1.2.3 Connect Flags - byte 8 */
                mqtt_packet_buf[index++] = (var_header_s.keep_alive >> 8) & 0xFF; /* Section 3.1.2.10 Keep Alive MSB - byte 9 */
                mqtt_packet_buf[index++] = (var_header_s.keep_alive & 0xFF); /* Section 3.1.2.10 Keep Alive LSB - byte 10 */
            }
            break;

        case MQTT_PUBLISH:
            {
                /* Currently only handle for QoS 0 */
                if (var_header_s.pub_topic_name == NULL) {
                    return -1;
                }
                uint8_t topic_sz = strlen(var_header_s.pub_topic_name);
                mqtt_packet_buf[index++] = 0x00;
                mqtt_packet_buf[index++] = topic_sz; /* Section 3.3.2.1 Topic Name */
                strcpy(&mqtt_packet_buf[index], var_header_s.pub_topic_name);
                index += topic_sz;
            }
            break;

        default:
            break;
    }
    return index;
}

int form_payload(uint8_t *mqtt_packet_buf, mqtt_payload_t payload_s) {
    int index = 0;
    if (mqtt_packet_buf == NULL) {
        return -1;
    }

    /* Form Client ID */
    if (payload_s.client_id != NULL) {
        mqtt_packet_buf[index++] = 0;
        mqtt_packet_buf[index++] = strlen(payload_s.client_id);
        strcpy(&mqtt_packet_buf[index], payload_s.client_id);
        index+=strlen(payload_s.client_id);
    }

    /* Form subscribe topic */
    if (payload_s.subscribe_topic != NULL) { /* Section 3.8.3 Payload */
        mqtt_packet_buf[index++] = strlen(payload_s.subscribe_topic) & 0xF0; // topic length MSB
        mqtt_packet_buf[index++] = strlen(payload_s.subscribe_topic) & 0x0F; // topic length LSB
        strcpy(&mqtt_packet_buf[index], payload_s.subscribe_topic);
        index += strlen(payload_s.subscribe_topic);

        mqtt_packet_buf[index++] = 0; // QoS 0
    }

    /* Form message, for publish packet, section 3.3 PUBLISH – Publish message */
    if (payload_s.message != NULL && payload_s.message_size != 0) {
        memcpy(&mqtt_packet_buf[index], payload_s.message, payload_s.message_size);
        index += payload_s.message_size;
    }

    /* form username, if specified, for connect packet, section 3.1.3.4 User Name */
    if (payload_s.user_name != NULL) {
        mqtt_packet_buf[index++] = 0;
        mqtt_packet_buf[index++] = strlen(payload_s.user_name);
        strcpy(&mqtt_packet_buf[index], payload_s.user_name);
        index += strlen(payload_s.user_name);
    }

    /* form password, if specified, for connect packet, section 3.1.3.5 Password */
    if (payload_s.password != NULL) {
        mqtt_packet_buf[index++] = 0;
        mqtt_packet_buf[index++] = strlen(payload_s.password);
        strcpy(&mqtt_packet_buf[index], payload_s.password);
        index += strlen(payload_s.password);
    }

    return index;
}