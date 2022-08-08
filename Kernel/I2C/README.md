# Fundamental concepts

I2C devices are not enumerated at the hardware level. Instead, the software must know which devices are connected on each I2C bus segment, and what address these devices are using. 

## Implementation

* I2C driver for specific I2C device: Not yet implemented in Ubuntu, check [the example in Raspbian for PCF8574](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Kernel#i2c-driver).
* [Create an I2C/SMBUS stub bus](i2c-stub.md)
