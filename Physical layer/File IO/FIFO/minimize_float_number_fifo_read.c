#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define FIFO_NAME 		"FIFO"
#define FILE_PERMISSION	 0777

#define UPPER_RANGE_VALUE   99.0f
#define SCALING_FACTOR      65535.0f

int main(int argc, char *argv[])  {
	uint8_t read_buffer[2];
    
	int fd = open(FIFO_NAME, O_RDONLY);
	if (fd == -1) {
		printf("Unable to open %s", FIFO_NAME);
		return 0;
	}	

	printf("Opened\n");

    while(1){
        read(fd, read_buffer, sizeof(char) * 2);
        uint16_t received_int_number = (int) (read_buffer[1]<<8) | read_buffer[0];
        printf("̀%d %d %d\n", read_buffer[0], read_buffer[1], received_int_number);

        float origin_float_number = received_int_number * UPPER_RANGE_VALUE / SCALING_FACTOR;

        printf("Received: %.2f\n", origin_float_number);
    }

	close(fd);
}
