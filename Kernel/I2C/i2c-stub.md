# Implementations

## Setup

**Set up before compiling**: Set slave address:

```c
static unsigned short chip_addr[MAX_CHIPS] = {0x03};
```

Before installing the module, there only 10 I2C bus: 

```
/dev/i2c-0  /dev/i2c-1  /dev/i2c-2  /dev/i2c-3  /dev/i2c-4  /dev/i2c-5  /dev/i2c-6  /dev/i2c-7  /dev/i2c-8  /dev/i2c-9
```

After installing, there are 11 bus with ``/dev/i2c-10``

Check with ``sudo i2cdetect 10``, there will be I2C slave with address ``0x03`` available.

## R/W operation

R/W operation can be performed normally with ``i2cset`` and ``i2cget``.

For I2C/SMBUS userspace function, ``i2c/smbus.h`` library is required, which is inside package ``libi2c-dev``.

Install

```sh
sudo apt-get install libi2c-dev
```

Compile: ``gcc test.c -li2c``

# API

```c
int i2c_smbus_read_i2c_block_data(int file, __u8 reg, __u8 length, __u8 *values)
int i2c_smbus_write_i2c_block_data(int file, __u8 reg, __u8 length, __u8 *values)
```

* ``file``: I2C bus file descriptor
* ``reg``: Register inside the I2C slave to R/W
* ``length``: Length of the ``__u8 *values`` buffer to R/W
* ``values``: Buffer value to R/W

**Return**: ``0`` if success

# Examples

* [i2c_stub_write.c](i2c_stub_write.c): Write 5 bytes of data to register ``0x00`` in I2C slave which has address ``0x03``
* [i2c_stub_read.c](i2c_stub_read.c): Read 5 bytes of data to register ``0x00`` in I2C slave which has address ``0x03``

For I2C stub bus created from i2c_stub program kernel module, ``i2c_smbus_write_i2c_block_data()`` must be use to write data. ``i2c_smbus_write_block_data()`` must not be used as it results in the wrong written operation although giving no compilation error:

```c
/*
  With I2C/SMBUS stub bus, also giving no error, i2c_smbus_write_block_data() in the program
  below will give wrong written value to address WR_REG and does not write value to WR_REG+1, WR_REG+2,... WR_REG + WRITE_SIZE - 1
*/
if (i2c_smbus_write_block_data(i2c_bus, WR_REG, WRITE_SIZE, wr_buf) < 0){
  printf("Unable write wr_buf\n");
  perror("DEBUG");
  return -1;
}
```

As the I2C/SMBus stub bus, ``read()`` and ``write()`` system call for I2C will not work and will give ``EOPNOTSUPP`` error (**Operation not support**)

```c
//This is a wrong write operation to I2C/SMBUS stub bus and will result in err Operation not permitted
if (write(i2c_bus, wr_buf, WRITE_SIZE) != 1){
  printf("Unable write wr_buf\n");
  perror("DEBUG");
  return -1;
}
```