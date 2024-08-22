#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

uint8_t value[] = {0x24, 0x00, 0x01, 0x1A, 0x05, 0x1f, 0x20, 0x2F, 0x1C, 0x17, 0x20, 0x61};

uint8_t dcd_header[1], id[2];
uint8_t env_humid[2], env_temp[2], soil_humid[2], soil_temp[2];
uint8_t checksum[1];

void struct_data_parsing(uint8_t *data);

int main(){
    struct_data_parsing(value);
    printf("dcd_header: 0x%x\n", dcd_header[0]);
    printf("ID: 0x%x 0x%x\n", id[0], id[1]);

    printf("env_humid: 0x%x 0x%x\n", env_humid[0], env_humid[1]);
    printf("env_temp: 0x%x 0x%x\n", env_temp[0], env_temp[1]);

    printf("soil_humid: 0x%x 0x%x\n", soil_humid[0], soil_humid[1]);
    printf("soil_temp: 0x%x 0x%x\n", soil_temp[0], soil_temp[1]);

    printf("checksum: 0x%x\n", checksum[0]);
}

void struct_data_parsing(uint8_t *data){
    struct data {
        uint8_t dcd_header[1];
        uint8_t id[2];
        uint8_t env_humid[2];
        uint8_t env_temp[2];
        uint8_t soil_humid[2];
        uint8_t soil_temp[2];
        uint8_t checksum[1];
    } data_frame;

    memcpy(&data_frame, data, sizeof(struct data));//As uint8_t* data is an array, so use fix value here (12), not strlen(data)

    memcpy(dcd_header, data_frame.dcd_header, sizeof(dcd_header));
    memcpy(id, data_frame.id, sizeof(id));

    memcpy(env_humid, data_frame.env_humid, sizeof(env_humid));
    memcpy(env_temp, data_frame.env_temp, sizeof(env_temp));
    memcpy(soil_humid, data_frame.soil_humid, sizeof(soil_humid));
    memcpy(soil_temp, data_frame.soil_temp, sizeof(soil_temp));

    memcpy(checksum, data_frame.checksum, sizeof(checksum));
}
