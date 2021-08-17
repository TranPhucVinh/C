### Sender

Perform a CRC-16-IBM generation on sender side

**Calculation steps**

* The starting value is 0xFFFF.
* Perform an XOR operation of this value and the slave address.
* Right shift the result.
* When the overflow bit of the result operation becomes 1, perform an XOR operation of the result from step 3 above and the fix value 0xA001.
* Repeat steps 3 and 4 until 8 shift operations have been performed.

**Program**

```c
#include <stdio.h>

int modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04};
int crc_16_ibm;

int main(){
    crc_16_ibm = 0xffff;
    for (int i = 0; i < sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]); i++){
        crc_16_ibm ^= modbus_rtu_frame[i];
        for (int j = 0; j < 8; j ++){
            if ((crc_16_ibm & 0x01) == 1) crc_16_ibm = ((crc_16_ibm>>1)^0xa001);
            else crc_16_ibm = crc_16_ibm >> 1;
        }
    }

    printf("%p\n", crc_16_ibm);//0x0944
}
```
### Receiver

The Modbus RTU transmitted frame will be: 

```c
int modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x944};
```

Perform the identical CRC calculation in receive like in master. If all Modbus RTU transmitted frame are well received, ``crc_16_ibm`` will be ``0``.

If there is error, like ``modbus_rtu_frame[2]`` has received the wrong value like ``0x05`` (instead of ``0x00``), then CRC will not be ``0``

```c
#include <stdio.h>

int modbus_rtu_frame[] = {0x01, 0x03, 0x05, 0x00, 0x00, 0x04, 0x944};
int crc_16_ibm;

int main(){
    crc_16_ibm = 0xffff;
    for (int i = 0; i < sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]); i++){
        crc_16_ibm ^= modbus_rtu_frame[i];
        for (int j = 0; j < 8; j ++){
            if ((crc_16_ibm & 0x01) == 1) crc_16_ibm = ((crc_16_ibm>>1)^0xa001);
            else crc_16_ibm = crc_16_ibm >> 1;
        }
    }

    printf("%p\n", crc_16_ibm);//0xcc
}
```