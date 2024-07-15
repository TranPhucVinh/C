#include "pub_sub.h"

int  form_fix_header(uint8_t *mqtt_packet_buf, mqtt_fix_header_t fix_header_s);
int  form_variable_header(uint8_t *mqtt_packet_buf, uint8_t control_type, mqtt_var_header_t var_header_s);
int  form_payload(uint8_t *mqtt_packet_buf, mqtt_payload_t payload_s);