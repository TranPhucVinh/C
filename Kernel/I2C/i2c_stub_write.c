#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> //for open()
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>//For I2C_SLAVE cmd
#include <i2c/smbus.h>

#define I2C_BUS 	"/dev/i2c-10"
#define SLAVE_ADDR	0x03
#define WR_REG		0x00
#define WRITE_SIZE	5

int main(int argc, char *argv[]) {
    int i2c_bus;

	i2c_bus = open(I2C_BUS, O_RDWR);
	if (i2c_bus < 0){
        printf("Unable to open I2C bus\n");
        return -1;
	}

    if (ioctl(i2c_bus, I2C_SLAVE, SLAVE_ADDR) < 0){
        printf("Unable to perform ioctl for PCF8574 as I2C slave\n");
        close(i2c_bus);
        return -1;
    }

	unsigned char wr_buf[WRITE_SIZE];

	for (int i = 0; i < WRITE_SIZE; i++){
		wr_buf[i] = i;//i2c_smbus_write_i2c_block_data
	}

	//That works perfectly
	if (i2c_smbus_write_i2c_block_data(i2c_bus, WR_REG, WRITE_SIZE, wr_buf) < 0){
		printf("Unable write wr_buf\n");
		perror("DEBUG");
		return -1;
	}
}	