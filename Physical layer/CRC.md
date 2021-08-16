### Sender

Perform a CRC-16-IBM generation on sender side

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

    printf("%p\n", crc_16_ibm);
}
```