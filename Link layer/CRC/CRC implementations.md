# CRC-16-IBM

### Sender

Perform a CRC-16-IBM generation on sender side

**Calculation steps**

1. Load a 16–bit register with FFFF hex (all 1’s). Call this the CRC register.
2. Exclusive OR the first 8–bit byte of the message with the low–order byte of the 16–bit CRC register, putting the result in the CRC register.
3. Shift the CRC register one bit to the right (toward the LSB), zero–filling the MSB. Extract and examine the LSB.
4. If the LSB was 0: Repeat Step 3 (another shift).
If the LSB was 1 (AND with ``0x01``): Exclusive OR the CRC register with the polynomial value ``0xA001`` (``1010 0000 0000 0001``).
5. Repeat Steps 3 and 4 until 8 shifts have been performed. When this is done, a complete 8–bit byte will have been
processed.
6. Repeat Steps 2 through 5 for the next 8–bit byte of the message. Continue doing this until all bytes have been processed.
7. The final content of the CRC register is the CRC value

**Program**

```c
#include <stdio.h>

int modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04};

int sender_crc_calculate(int *modbus_rtu_frame, int size){
    int crc_16_ibm = 0xffff;
    for (int i = 0; i < size; i++){
        crc_16_ibm ^= modbus_rtu_frame[i];
        for (int j = 0; j < 8; j ++){
            if ((crc_16_ibm & 0x01) == 1) crc_16_ibm = ((crc_16_ibm>>1)^0xa001);
            else crc_16_ibm = crc_16_ibm >> 1;
        }
    }
    return crc_16_ibm;
}

int main(){
    int crc_16_ibm = sender_crc_calculate(modbus_rtu_frame, sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]));
    printf("%p\n", crc_16_ibm);//0x0f24

    /*
        Then form an array include CRC
        uint8_t modbus_rtu_frame_with_crc[] = {... data member ..., crc_low_byte, crc_high_byte};
    */
    uint8_t modbus_rtu_frame_with_crc[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, crc_16_ibm, crc_16_ibm>>8};

    for (int i=0; i < sizeof(modbus_rtu_frame_with_crc)/sizeof(modbus_rtu_frame_with_crc[0]); i++){
        printf("%p ", modbus_rtu_frame_with_crc[i]);
    }
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
#include <stdint.h>

int modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x944};

int receiver_crc_calculate(int *modbus_rtu_frame, int size){
    int crc_16_ibm = 0xffff;
    for (int i = 0; i < size; i++){
        crc_16_ibm ^= modbus_rtu_frame[i];
        for (int j = 0; j < 8; j ++){
            if ((crc_16_ibm & 0x01) == 1) crc_16_ibm = ((crc_16_ibm>>1)^0xa001);
            else crc_16_ibm = crc_16_ibm >> 1;
        }
    }
    return crc_16_ibm;
}

int main(){
    int crc_16_ibm = receiver_crc_calculate(modbus_rtu_frame, sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]));
    if (!crc_16_ibm) printf("No error happens during transmission with CRC is %d", crc_16_ibm);
    else printf("Error happens during transmission with CRC is %p\n", crc_16_ibm);
}
```
For proper storing and display, use ``uint8_t`` for ``modbus_rtu_frame`` and use ``uint8_t`` as ``receiver_crc_calculate()`` function parameter:

```c
uint8_t modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09};
int receiver_crc_calculate(uint8_t *modbus_rtu_frame, int size){
    //Identical declartion like example above
}    
```

If using ``uint8_t modbus_rtu_frame[]`` and ``int`` as ``receiver_crc_calculate()`` function parameter, there will be CRC error:

```c
uint8_t modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09};
int receiver_crc_calculate(int *modbus_rtu_frame, int size){
    //Identical declartion like example above
}    

int main(){
    int crc_16_ibm = receiver_crc_calculate((int*)modbus_rtu_frame, sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]));
    if (!crc_16_ibm) printf("No error happens during transmission with CRC is %d", crc_16_ibm);
    else printf("Error happens during transmission with CRC is %p\n", crc_16_ibm);
}
```
**Result**

```
Error happens during transmission with CRC is 0xd040
```

## Perform a CRC-16-IBM calculation

```c
#include <Arduino.h>

int modbus_rtu_frame[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01};

int sender_crc_calculate(int *modbus_rtu_frame, int size){
    uint16_t crc_16_ibm = 0xffff;
    for (int i = 0; i < size; i++){
        crc_16_ibm ^= modbus_rtu_frame[i];
        for (int j = 0; j < 8; j ++){
            if ((crc_16_ibm & 0x01) == 1) crc_16_ibm = ((crc_16_ibm>>1)^0xa001);
            else crc_16_ibm = crc_16_ibm >> 1;
        }
    }
    return crc_16_ibm;
}

void setup(){
    Serial.begin(9600);
}

void loop(){
    int crc_16_ibm = sender_crc_calculate(modbus_rtu_frame, sizeof(modbus_rtu_frame)/sizeof(modbus_rtu_frame[0]));
    Serial.println(crc_16_ibm, HEX);//0xf24
	delay(1000);
}
```
**Note**: Inside ``sender_crc_calculate()``, if define ``int crc_16_ibm = 0xffff``, the result will be wrong although int is 16-bit in AVR Arduino framework.

# CRC-8-Dallas-Maxim

```c
#include <stdio.h>
#include <stdint.h>

uint8_t one_wire_frame[] = {0xbe, 0xef};

uint8_t sender_crc_calculate(uint8_t *one_wire_frame, uint8_t size){
	uint8_t crc = 0xff;
	for (size_t i = 0; i < size; i++) {
		crc ^= one_wire_frame[i];
		for (size_t j = 0; j < 8; j++) {
			if ((crc & 0x80) != 0) {
				crc = ((crc << 1u) ^ 0x31);
			} else {
				crc <<= 1u;
			}
		}
	}
	return crc;
}

int main(){
    int crc_8_dallas_maxim = sender_crc_calculate(one_wire_frame, sizeof(one_wire_frame)/sizeof(one_wire_frame[0]));
    printf("%p\n", crc_8_dallas_maxim);//0x92
}
```
