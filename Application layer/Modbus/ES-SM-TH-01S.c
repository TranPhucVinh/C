#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define ADDRESS_CODE          0x01
#define FUNCTION_CODE         0x03
#define SOIL_HUMID_REG_MSB    0x00
#define SOIL_HUMID_REG_LSB    0x12
#define NUM_OF_REGISTER_MSB   0x00
#define NUM_OF_REGISTER_LSB   0x01
#define MOBUS_RTU_FRAME_SIZE  8
#define READ_BUFFER           20

const char filePath[] = "/dev/ttyUSB0";

uint8_t modbus_rtu_frame[] = {ADDRESS_CODE, FUNCTION_CODE, SOIL_HUMID_REG_MSB, SOIL_HUMID_REG_LSB, NUM_OF_REGISTER_MSB, NUM_OF_REGISTER_LSB};
uint8_t modbus_rtu_frame_with_crc[MOBUS_RTU_FRAME_SIZE];
uint8_t soil_sensor_data[READ_BUFFER];
int 	fileDescription;
int     crc_16_ibm;

int  	sender_crc_calculate(uint8_t *modbus_rtu_frame, int size);
void 	form_modbus_rtu_frame();
void 	read_sensor_data(uint8_t *read_buffer);
void 	delaySeconds(long seconds);

int main(){
	fileDescription = open(filePath, O_RDWR);
	form_modbus_rtu_frame();
	while(1){
		write(fileDescription, modbus_rtu_frame_with_crc, MOBUS_RTU_FRAME_SIZE);
		read(fileDescription, soil_sensor_data, READ_BUFFER);
		printf("%x %x %x %x %x %x\n", soil_sensor_data[0], soil_sensor_data[1], 
		soil_sensor_data[2], soil_sensor_data[3], 
		soil_sensor_data[4], soil_sensor_data[5]);
		delaySeconds(1);
	}
    return 0;
}

void delaySeconds(long seconds){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long totalSecond = 0;
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}

int sender_crc_calculate(uint8_t *modbus_rtu_frame, int size){
    uint16_t crc_16_ibm = 0xffff;
    for (int i = 0; i < size; i++){
        crc_16_ibm ^= modbus_rtu_frame[i];
        for (int j = 0; j < 8; j ++){
            if ((crc_16_ibm & 0x01) == 1) crc_16_ibm = ((crc_16_ibm>>1)^0xa001);
            else crc_16_ibm = crc_16_ibm >> 1;
        }
    }
    return crc_16_ibm;
}

void form_modbus_rtu_frame(){
	int frame_size_without_crc = sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]);
	crc_16_ibm = sender_crc_calculate(modbus_rtu_frame, frame_size_without_crc);	

	for (int i = 0; i < frame_size_without_crc; i++){
		modbus_rtu_frame_with_crc[i] = modbus_rtu_frame[i];
	}

	modbus_rtu_frame_with_crc[MOBUS_RTU_FRAME_SIZE-2] =  crc_16_ibm;
	modbus_rtu_frame_with_crc[MOBUS_RTU_FRAME_SIZE-1] =  crc_16_ibm>>8;
}
