## Example 1

### struct as a function argument
```c
#include <stdio.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

void structFunction(struct databaseNode node);

main(){
	struct databaseNode node = {1, "String value"};
	structFunction(node);
}

void structFunction(struct databaseNode node){
	printf("id is %d and string value is %s \n", node.id, node.stringValue);
}
```
### struct function

```c
#include <stdio.h>
#include <string.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

struct databaseNode displayString();

main(){
    struct databaseNode returnNode = displayString();
    printf("returnNode.id: %d, returnNode.stringValue: %s", returnNode.id, returnNode.stringValue);
}

struct databaseNode displayString(){
    struct databaseNode node;
    node.id = 1;
    strcpy(node.stringValue, "Hello, World !");

    return node;
}
```

``struct`` a type with ``typedef``:

```c
#include <stdio.h>
#include <string.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

typedef struct databaseNode Database;

Database displayString();

int main() {
	displayString();
}

Database displayString(){
    Database node;
    node.id = 1;
    strcpy(node.stringValue, "Hello, World !");
    printf("node.id %d, node.stringValue: %s\n", node.id, node.stringValue);
}
```
## Example 2

Nested struct

```c
struct linkedDatabaseNode{
    int id;
    char stringValue[50];
};

struct databaseNode  
{
   int id;
   struct linkedDatabaseNode nextNode;
};

int main()
{
    struct databaseNode databaseNode0 = {1, 2, "Displayed string"};
    printf("Member databaseNode0 has id %d\n", databaseNode0.id); 

    printf("ID of databaseNode0 from linkedDatabaseNode is %d, and the displayed string: %s", databaseNode0.nextNode.id, databaseNode0.nextNode.stringValue);
}
```

**Output**

```
Member databaseNode0 has id 1
ID of databaseNode0 from linkedDatabaseNode is 2, and the displayed string: Displayed string
```
### Example 3

Parsing a char array into the following fields

Char array: ``0x24 0x00 0x01 0x1A 0x05 0x1F 0x20 0x2F 0x1C 0x17 0x20 0x61``

* DCD header: ``$`` (``0x24``)
* ID: ``0001`` (``0x00`` ``0x01``)
* Environment humidity: ``26,05`` (``0x1A`` ``0x05``)
* Environment temperature: ``31,32``(``0x1F`` ``0x20``)
* Soil humidity: ``47,28`` (``0x2F`` ``0x1C``)
* Soil temperature: ``23,32`` (``0x17`` ``0x20``)
* Checksum: 0x61 (OR 11 bytes give 0x0261, 0x61 is the lower byte)

**Program**

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT_FD 1
char value[] = {0x24, 0x00, 0x01, 0x1A, 0x05, 0x1f, 0x20, 0x2F, 0x1C, 0x17, 0x20, 0x61};

void uart_data_parsing(char *data);

int main(){
    uart_data_parsing(value);
}

void uart_data_parsing(char *data){
    char dcd_header[1], id[8], checksum[8];
    char environment_humidity[9], environment_temperature[9], soil_humidity[9], soil_temperature[9];

    struct data {
        char dcd_header[1];
        char id[2];
        char environment_humidity[2];
        char environment_temperature[2];
        char soil_humidity[2];
        char soil_temperature[2];
        char checksum[1];
    } data_frame;

    // For char array with hex value, using strcpy() will result in error
    memcpy(&data_frame, data, 12);

    //dcd_header parsing
    sprintf(dcd_header, "%c", data_frame.dcd_header[0]);

    //id parsing
    if (data_frame.id[0] < 10) sprintf(id, "0%d", data_frame.id[0]);
    else sprintf(id, "%d", data_frame.id[0]);

    if (data_frame.id[1] < 10) sprintf(id, "%s0%d", id, data_frame.id[1]);
    else sprintf(id, "%s%d", id, data_frame.id[1]);

    //environment_humidity parsing
    if (data_frame.environment_humidity[0] < 10) sprintf(environment_humidity, "0%d", data_frame.environment_humidity[0]);
    else sprintf(environment_humidity, "%d", data_frame.environment_humidity[0]);

    if (data_frame.environment_humidity[1] < 10) sprintf(environment_humidity, "%s.0%d", environment_humidity, data_frame.environment_humidity[1]);
    else sprintf(environment_humidity, "%s.%d", environment_humidity, data_frame.environment_humidity[1]);

    //environment_temperature parsing
    if (data_frame.environment_temperature[0] < 10) sprintf(environment_temperature, "0%d", data_frame.environment_temperature[0]);
    else sprintf(environment_temperature, "%d", data_frame.environment_temperature[0]);

    if (data_frame.environment_temperature[1] < 10) sprintf(environment_temperature, "%s.0%d", environment_temperature, data_frame.environment_temperature[1]);
    else sprintf(environment_temperature, "%s.%d", environment_temperature, data_frame.environment_temperature[1]);

    //soil_humidity parsing
    if (data_frame.soil_humidity[0] < 10) sprintf(soil_humidity, "0%d", data_frame.soil_humidity[0]);
    else sprintf(soil_humidity, "%d", data_frame.soil_humidity[0]);

    if (data_frame.soil_humidity[1] < 10) sprintf(soil_humidity, "%s.0%d", soil_humidity, data_frame.soil_humidity[1]);
    else sprintf(soil_humidity, "%s.%d", soil_humidity, data_frame.soil_humidity[1]);

    //soil_temperature parsing
    if (data_frame.soil_temperature[0] < 10) sprintf(soil_temperature, "0%d", data_frame.soil_temperature[0]);
    else sprintf(soil_temperature, "%d", data_frame.soil_temperature[0]);

    if (data_frame.soil_temperature[1] < 10) sprintf(soil_temperature, "%s.0%d", soil_temperature, data_frame.soil_temperature[1]);
    else sprintf(soil_temperature, "%s.%d", soil_temperature, data_frame.soil_temperature[1]);

    // checksum parsing
    sprintf(checksum, "%x", data_frame.checksum[0]);
}
```