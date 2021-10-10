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