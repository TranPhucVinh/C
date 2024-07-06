# Serialize

Serialization is the process of translating a data structure or object state into a format that can be stored (for example, in a file or memory data buffer) or transmitted (for example, over a computer network) and reconstructed later (possibly in a different computer environment). Several data-serialization formats are JSON, CSV, XML and others are popular. **Deserialization** is the opposite process.

# Minimize float number to send as array member with 1 byte

## Fundamental concepts

Transmission of a float number (which has size of 4 bytes in GCC and in various MCU compiler like AVR Arduino) can be minimize into 2 bytes by using 2 char value. (1 char has the size of 1 byte). This can be achieved by using the approximate method in the range of n byte.

Theoretically, n bit can used to present/approximate the value of a number. The bigger value of n, the more precise it can approximate the value.

In this case, we use 16 bit (2 byte with has int value of 65535) value as an integer number to approximate the value of a float number. ``65535`` now is the scaling factor

**Transmitter side**

Take this conversion process:

UPPER_RANGE_VALUE -> 65535

float_value	-> converted_int_value

Where ``UPPER_RANGE_VALUE`` is the max value used in the coversion range.

Then ``converted_int_value = float_value * (65535 / UPPER_RANGE_VALUE)``

Then form a char array with 2 member to store ``converted_int_value``:

```c
/*
  It's better to use uint8_t for sending unsigned int value instead of char, this will avoid the signess issue in the receiver side when converting the received int value back to float, as GCC/G++ might consider some value as value with sign.
  That issue happen as in GCC and G++, the default char type is signed char.
*/
uint8_t array[2];
array[0] = (uint8_t)converted_int_value; //LSB
array[1] = converted_int_value >> 8; //MSB
```

Then start sending ``array``.

**Receiver side**

Converted the received value back to the orignal value:

```c
uint8_t read_buffer[2];
uint16_t received_int_number = (int) (read_buffer[1]<<8) | read_buffer[0];
float origin_float_number = received_int_number * UPPER_RANGE_VALUE  / 65535.0f;
```

Bigger value (with bigger bit like 17-bit) can be used for scaling factor, e.g ``70000``. However the overflow issue which results in worng received value in receiver side should be concerned. Also notice that this method use ``int`` value to map to the ``float`` value, so the scaling factor should also be care so that it will result in the converted value lies in the range of ``int``.

## Implementation

1. [Using this method to send data by FIFO in 2 process on Ubuntu OS](../Physical%20layer/File%20IO/FIFO/README.md#IPC%20by%20FIFO%20with%20scaling%20data%20method) by FIFO with scaling data method.
2. Query and response data in LoRa transmission:
* [duplex_receive_and_send.cpp](https://github.com/TranPhucVinh/ESP32-Arduino-framework/blob/master/Sensors%20and%20Modules/LoRa/duplex_receive_and_send.cpp): Being queried data by another LoRa node then sends a random float number under the minimize form as int number to that node.
