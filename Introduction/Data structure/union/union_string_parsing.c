#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT_FD 1
char value[] = {0x24, 0x00, 0x01, 0x1A, 0x05, 0x1f, 0x20, 0x2F, 0x1C, 0x17, 0x20, 0x61};

void union_string_parsing(char *data);

/*
    The buffer for each member must be bigger enough to store the parse value. If its size is not big, there will be problem of losing the value
    E.g:
    checksum[8] for 2 int values
    environment_humidity[9] for 2 int values and a '.' symbol
*/    
char dcd_header[1], id[8], checksum[8];
char environment_humidity[9], environment_temperature[9], soil_humidity[9], soil_temperature[9];

int main(){
    union_string_parsing(value);

    write(STDOUT_FD, dcd_header, sizeof(dcd_header));
    printf("\n");

    write(STDOUT_FD, id, sizeof(id));
    printf("\n");

    write(STDOUT_FD, environment_humidity, sizeof(environment_humidity));
    printf("\n");

    write(STDOUT_FD, environment_temperature, sizeof(environment_temperature));
    printf("\n");

    write(STDOUT_FD, soil_humidity, sizeof(soil_humidity));
    printf("\n");

    write(STDOUT_FD, soil_temperature, sizeof(soil_temperature));
    printf("\n");

    write(STDOUT_FD, checksum, sizeof(checksum));
    printf("\n");
}

void union_string_parsing(char *data){
    union data_frame {
        struct data {
            char dcd_header[1];
            char id[2];
            char environment_humidity[2];
            char environment_temperature[2];
            char soil_humidity[2];
            char soil_temperature[2];
            char checksum[1];
        } data;
        char data_storage[12];
    } frame;

    // For char array with hex value, using strcpy() will result in error
    memcpy(frame.data_storage, data, 12);

    //dcd_header parsing
    sprintf(dcd_header, "%c", frame.data.dcd_header[0]);

    //id parsing
    if (frame.data.id[0] < 10) sprintf(id, "0%d", frame.data.id[0]);
    else sprintf(id, "%d", frame.data.id[0]);

    if (frame.data.id[1] < 10) sprintf(id, "%s0%d", id, frame.data.id[1]);
    else sprintf(id, "%s%d", id, frame.data.id[1]);

    //environment_humidity parsing
    if (frame.data.environment_humidity[0] < 10) sprintf(environment_humidity, "0%d", frame.data.environment_humidity[0]);
    else sprintf(environment_humidity, "%d", frame.data.environment_humidity[0]);

    if (frame.data.environment_humidity[1] < 10) sprintf(environment_humidity, "%s.0%d", environment_humidity, frame.data.environment_humidity[1]);
    else sprintf(environment_humidity, "%s.%d", environment_humidity, frame.data.environment_humidity[1]);

    //environment_temperature parsing
    if (frame.data.environment_temperature[0] < 10) sprintf(environment_temperature, "0%d", frame.data.environment_temperature[0]);
    else sprintf(environment_temperature, "%d", frame.data.environment_temperature[0]);

    if (frame.data.environment_temperature[1] < 10) sprintf(environment_temperature, "%s.0%d", environment_temperature, frame.data.environment_temperature[1]);
    else sprintf(environment_temperature, "%s.%d", environment_temperature, frame.data.environment_temperature[1]);

    //soil_humidity parsing
    if (frame.data.soil_humidity[0] < 10) sprintf(soil_humidity, "0%d", frame.data.soil_humidity[0]);
    else sprintf(soil_humidity, "%d", frame.data.soil_humidity[0]);

    if (frame.data.soil_humidity[1] < 10) sprintf(soil_humidity, "%s.0%d", soil_humidity, frame.data.soil_humidity[1]);
    else sprintf(soil_humidity, "%s.%d", soil_humidity, frame.data.soil_humidity[1]);

    //soil_temperature parsing
    if (frame.data.soil_temperature[0] < 10) sprintf(soil_temperature, "0%d", frame.data.soil_temperature[0]);
    else sprintf(soil_temperature, "%d", frame.data.soil_temperature[0]);

    if (frame.data.soil_temperature[1] < 10) sprintf(soil_temperature, "%s.0%d", soil_temperature, frame.data.soil_temperature[1]);
    else sprintf(soil_temperature, "%s.%d", soil_temperature, frame.data.soil_temperature[1]);

    // checksum parsing
    sprintf(checksum, "%x", frame.data.checksum[0]);
}