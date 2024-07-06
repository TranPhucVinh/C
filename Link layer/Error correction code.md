# Fundamental concepts

Error correction code, also known as error-detecting code, is a technique used for controlling errors in data transmission over communication channels like I2C, SPI, UART,...

There are many error detection code methods:
* VRC (vertical redundancy check): Check for odd/parity number of bit 1 inside a unit of data
* LRC (longitudinal redundancy check): Check for odd/parity number of bit 1 inside a block of data
* [CRC (cyclic redundancy check)](CRC)
* Checksum

Among those, CRC is the most efficient method.

In any error correction code methods, the sender side will calculate the error correction code, based on this method algorithm, for the whole transmitted data then insert that error correction code at the end of it.

Suppose that ``uint8_t array[]`` is transmitted from the sender to the receiver:

```c
uint8_t array[] = {0x01, 0x44, 0x40, 0x67, 0x78};
```

Due to error, the receive will receive: 

```c
{0x01, 0x44, 0x45, 0x67, 0x78};
```

Where ``array[2] = 0x45`` is the error byte.

Error-detection code will detect that error by inserting n bytes into the transmitted data, where those bytes are calculated based on the error detecion code (CRC, checksum,...) 

The pseudo code for this operation will be:

```cpp
auto error_detection_code_function(transmit_data){
    //Perform operations here to calculate the bytes_to_be_inserted_for_error_detection bytes
    return bytes_to_be_inserted_for_error_detection;
}
```
Where:

* ``error_detection_code_function``: Function to perform error-detection code
* ``transmit_data``: The data to be transmitted, it can be an array like ``uint8_t array[]`` above
* ``bytes_to_be_inserted_for_error_detection``: Bytes to be inserted into the ``transmit_data`` for error detection

Example:

With ``uint8_t array[]`` above, for example if the newly inserted error-detection code bytes are ``{0x56, 0x67}`` (returned from ``error_detection_code_function()``), then the whole ``array`` to be trasmitted will be:

```c
uint8_t array[] = {0x01, 0x44, 0x40, 0x67, 0x78, 0x56, 0x67};
```

The receiver side when receiving that ``array`` will perform the error-detection code check. As both sender and receiver sides has the same error-detection code check method, the receiver will know inside ``array``, which bytes are the transmitted data, which bytes are the error detection code inserted bytes.

So in this case, the receiver side will be able to split ``array`` into:

```cpp
uint8_t transmitted_data[] = {0x01, 0x44, 0x40, 0x67, 0x78};
uint8_t error_detection_code[] = {0x56, 0x67};
```

The receiver will then perform:

```cpp
auto error_detection_code_function(transmitted_data){
    //Perform operations here to calculate the bytes_to_be_inserted_for_error_detection bytes
    return bytes_to_be_inserted_for_error_detection;
}
```

If ``bytes_to_be_inserted_for_error_detection`` (returned from ``error_detection_code_function()``) is equal to ``error_detection_code``, then there will no error.

When there are transmission error as the receiver receives:

```c
uint8_t received_data[] = {0x01, 0x44, 0x45, 0x67, 0x78, 0x56, 0x67};//where the error byte array[2] = 0x45, instead of 0x40
```

After calling ``error_detection_code_function()`` function, ``bytes_to_be_inserted_for_error_detection`` (returned from ``error_detection_code_function()``) will be different from ``error_detection_code``, then the receiver will be know **there is a transmission error**.

# [CRC](CRC)