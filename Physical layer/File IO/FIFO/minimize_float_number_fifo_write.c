#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME 		"FIFO"
#define FILE_PERMISSION	 0777

#define LOWER 	            99
#define UPPER	            0

#define UPPER_RANGE_VALUE   99

char write_string[50];

float generate_random_number(float lower, float upper)
{
	return (float)rand()/(float)(RAND_MAX) * (upper- lower) + lower;
}
  
int main(int argc, char *argv[])  {
	if(mkfifo(FIFO_NAME, FILE_PERMISSION) == -1){
		printf("WARNING: A FIFO with the same name has already existed\n");

        //Use unlink() to remove the existed FIFO with the same name if existed
        if (!remove(FIFO_NAME)) {
            printf("FIFO %s has been deleted\n", FIFO_NAME);

            //Then create that FIFO again
            if (!mkfifo(FIFO_NAME, FILE_PERMISSION)) printf("FIFO %s has been recreated\n", FIFO_NAME);
        } else {
            printf("Unable to remove FIFO %s", FIFO_NAME);
            return 1;
        }
	} else printf("FIFO %s has been created\n", FIFO_NAME);

	int fd = open(FIFO_NAME, O_WRONLY);//Open for write
	if (fd == -1) {
		printf("Unable to open %s", FIFO_NAME);
		return 0;
	}	

	while(1){
        uint8_t array[2];
        float float_value = generate_random_number(LOWER, UPPER);
        int converted_int_value = float_value * (65535 / UPPER_RANGE_VALUE);

        array[0] = (uint8_t)converted_int_value; //LSB
        array[1] = converted_int_value >> 8; //MSB

        if (write(fd, array, sizeof(char) * 2) != -1) {
            printf("̀%d %d %d\n", array[0], array[1], converted_int_value);
            printf("̀Tranmit value: %.2f\n", float_value);
        }
        
        sleep(1);  
    }
    close(fd);
}