# Form an ``uint16_t`` number from 2 ``uint8_t`` numbers with ``struct``

```c
#include <stdio.h>
#include <stdint.h>

typedef struct
{
	uint8_t number_1;
	uint8_t number_2;
} struct_number;

struct_number number;

uint16_t number_3;

int main()
{
	number.number_1 = 0x12;
	number.number_2 = 0x34;

	number_3 = *(uint16_t*)(&number.number_1);
	printf("0x%x\n", number_3); //0x3412
}
```
# Split a string into specific string sequences

Split a string into the following sequence: ``host`` and ``port``

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char displayed[] = "demo.thingsboard.io443";
char host[19];
char port[3];

void struct_data_parsing(char *data);

int main() {
	struct_data_parsing(displayed);

    // printf("%s %s\n", host, port); // printf() will print out the wrong string
    write(STDOUT_FILENO, host, sizeof(host)); // demo.thingsboard.io
    printf("\n");
    write(STDOUT_FILENO, port, sizeof(port)); // 443
} 

void struct_data_parsing(char *data){
    struct struct_data {
        char host[19];
        char port[3];
    } data_frame;

    memcpy(&data_frame, data, strlen(data));
    strcpy(host, data_frame.host);
    strcpy(port, data_frame.port);
}
```

Result: View the result by ``gdb``

* host: demo.thingsboard.io
* port: 443

However, the way of parsing the communication protocol message from string into smaller strings isn't an effective way. Take this example as a failure of this method.

**Error when parsing the string array into the string as numbers**:

Parse string array ``130.8175.0016.40`` into:

* id = 1
* temperature = 30.81
* humidity = 75.00
* soil_humidity = 26.40

```c
#include <stdio.h>

char value[] = "130.8175.0026.40";

char id[1];
char temperature[5], humidity[5], soil_humidity[5];

void delay_seconds(long seconds);
void struct_data_parsing(char *value);

int main(int argc, char *argv[]){
    struct_data_parsing(value);	
	return 0;
}

void struct_data_parsing(char *value){
    struct data {
		char id[1];
		char temperature[5]; 
		char humidity[5];
		char soil_humidity[5];
    } data_frame;

    memcpy(&data_frame, value, strlen(value));

	strcpy(id, data_frame.id);
    strcpy(temperature, data_frame.temperature);
	strcpy(humidity, data_frame.humidity);
	strcpy(soil_humidity, data_frame.soil_humidity);
}
```

Result:

* id = 7
* temperature = 16.04
* humidity = 75.00
* soil_humidity = 16.40

So parsing a raw string containing number into string number will cause errror.

**Problem solved**: Convert string to hex value, check [Parsing a hex char array](#parsing-a-hex-char-array).

# Parse a communication protocol message by struct

Char array: ``0x24 0x00 0x01 0x1A 0x05 0x1F 0x20 0x2F 0x1C 0x17 0x20 0x61``

Parsing this char array into the following fields:

* DCD header: ``$`` (``0x24``)
* ID: ``0001`` (``0x00`` ``0x01``)
* Environment humidity: ``26.05`` (``0x1A`` ``0x05``)
* Environment temperature: ``31.32``(``0x1F`` ``0x20``)
* Soil humidity: ``47.28`` (``0x2F`` ``0x1C``)
* Soil temperature: ``23.32`` (``0x17`` ``0x20``)
* Checksum: 0x61 (OR 11 bytes give 0x0261, 0x61 is the lower byte)

**Program**: [parse_protocol_msg_by_struct.c](../src/parse_protocol_msg_by_struct.c)
