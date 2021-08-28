#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT_FD 1
char value[] = {0x24, 0x00, 0x01, 0x1A, 0x05, 0x1f, 0x20, 0x2F, 0x1C, 0x17, 0x20, 0x61};

void struct_data_parsing(char *data);

int main(){
    struct_data_parsing(value);
}

void struct_data_parsing(char *data){
    char dcd_header[1], id[8], checksum[8];
    char environment_humidity[9], environment_temperature[9], soil_humidity[9], soil_temperature[9];

    struct data {
        char dcd_header[1];
        char id[2];
        char environment_humidity[2];
        char environment_temperature[2];
        char soil_humidity[2];
        char soil_temperature[2];
        char checksum[1];
    } data_frame;

    // For char array with hex value, using strcpy() will result in error
    memcpy(&data_frame, data, 12);

    //dcd_header parsing
    sprintf(dcd_header, "%c", data_frame.dcd_header[0]);

    //id parsing
    if (data_frame.id[0] < 10) sprintf(id, "0%d", data_frame.id[0]);
    else sprintf(id, "%d", data_frame.id[0]);

    if (data_frame.id[1] < 10) sprintf(id, "%s0%d", id, data_frame.id[1]);
    else sprintf(id, "%s%d", id, data_frame.id[1]);

    //environment_humidity parsing
    if (data_frame.environment_humidity[0] < 10) sprintf(environment_humidity, "0%d", data_frame.environment_humidity[0]);
    else sprintf(environment_humidity, "%d", data_frame.environment_humidity[0]);

    if (data_frame.environment_humidity[1] < 10) sprintf(environment_humidity, "%s.0%d", environment_humidity, data_frame.environment_humidity[1]);
    else sprintf(environment_humidity, "%s.%d", environment_humidity, data_frame.environment_humidity[1]);

    //environment_temperature parsing
    if (data_frame.environment_temperature[0] < 10) sprintf(environment_temperature, "0%d", data_frame.environment_temperature[0]);
    else sprintf(environment_temperature, "%d", data_frame.environment_temperature[0]);

    if (data_frame.environment_temperature[1] < 10) sprintf(environment_temperature, "%s.0%d", environment_temperature, data_frame.environment_temperature[1]);
    else sprintf(environment_temperature, "%s.%d", environment_temperature, data_frame.environment_temperature[1]);

    //soil_humidity parsing
    if (data_frame.soil_humidity[0] < 10) sprintf(soil_humidity, "0%d", data_frame.soil_humidity[0]);
    else sprintf(soil_humidity, "%d", data_frame.soil_humidity[0]);

    if (data_frame.soil_humidity[1] < 10) sprintf(soil_humidity, "%s.0%d", soil_humidity, data_frame.soil_humidity[1]);
    else sprintf(soil_humidity, "%s.%d", soil_humidity, data_frame.soil_humidity[1]);

    //soil_temperature parsing
    if (data_frame.soil_temperature[0] < 10) sprintf(soil_temperature, "0%d", data_frame.soil_temperature[0]);
    else sprintf(soil_temperature, "%d", data_frame.soil_temperature[0]);

    if (data_frame.soil_temperature[1] < 10) sprintf(soil_temperature, "%s.0%d", soil_temperature, data_frame.soil_temperature[1]);
    else sprintf(soil_temperature, "%s.%d", soil_temperature, data_frame.soil_temperature[1]);

    // checksum parsing
    sprintf(checksum, "%x", data_frame.checksum[0]);
}