#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> //for open()
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>//For I2C_SLAVE cmd
#include <i2c/smbus.h>

#define I2C_BUS 	"/dev/i2c-10"
#define SLAVE_ADDR	0x03
#define RD_REG		0x00
#define READ_SIZE	5

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

	unsigned char rd_buf[READ_SIZE];

	//That works perfectly
	if (i2c_smbus_read_i2c_block_data(i2c_bus, RD_REG, READ_SIZE, rd_buf) < 0){
		printf("Unable write wr_buf\n");
		perror("DEBUG");
		return -1;
	} else {
		for (int i = 0; i < READ_SIZE; i++){
			printf("Value at 0x%x: %d\n", RD_REG+i, rd_buf[i]);
		}
	}
}	