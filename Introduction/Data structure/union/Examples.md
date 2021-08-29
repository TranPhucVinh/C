## Example 1

``union`` as function argument

```c
#include <stdio.h>
#include <string.h>

union data {
   int i;
   float f;
   char str[20];
}; 

void unionFunction(union data data0);

int main(){
    union data dataObject;
    unionFunction(dataObject);
}

void unionFunction(union data data0){
    data0.i = 1;
    printf("data.i: %d\n", data0.i);

    data0.f = 1.0;
    printf("data.f: %f\n", data0.f);

    strcpy( data0.str, "hello");
    printf("data.str: %s\n", data0.str);
}
```

## Example 2

Using ``struct`` inside ``union`` to split a string with the following sequence ``id``,  ``command`` and ``check_sum``

E.g: ``12345`` has ``id`` is ``1``, ``command`` is ``234`` and ``check_sum`` is ``5``.

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT_FD 1
char value[] = "12345";

union data_frame {
    struct data {
        char id[1];
        char command[3];
        char check_sum[1];
    } data;
    char data_storage[5];
};

int main(){
    union data_frame frame;

    strcpy(frame.data_storage, value);

    write(STDOUT_FD, frame.data.id, sizeof(frame.data.id));
    printf("\n");
    write(STDOUT_FD, frame.data.command, sizeof(frame.data.command));
    printf("\n");
    write(STDOUT_FD, frame.data.check_sum, sizeof(frame.data.check_sum));
    printf("\n");
}
```
**Note**

As memory order, the order of members defined inside ``struct data`` must follow the expected parsing order of the string, i.e ``id``, ``command`` and ``check_sum``.

Using ``printf()`` like this will cause error:

```c
printf("%s\n", frame.data.id);//12345
printf("%s\n", frame.data.command);//2345
printf("%s\n", frame.data.check_sum);//5
```
## Example 3

Parsing a char array into the following fields

Char array: ``0x24 0x00 0x01 0x1A 0x05 0x1F 0x20 0x2F 0x1C 0x17 0x20 0x61``

* DCD header: ``$`` (``0x24``)
* ID: ``0001`` (``0x00`` ``0x01``)
* Environment humidity: ``26,05`` (``0x1A`` ``0x05``)
* Environment temperature: ``31,32``(``0x1F`` ``0x20``)
* Soil humidity: ``47,28`` (``0x2F`` ``0x1C``)
* Soil temperature: ``23,32`` (``0x17`` ``0x20``)
* Checksum: 0x61 (OR 11 bytes give 0x0261, 0x61 is the lower byte)

### Program

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT_FD 1
char value[] = {0x24, 0x00, 0x01, 0x1A, 0x05, 0x1f, 0x20, 0x2F, 0x1C, 0x17, 0x20, 0x61};

void uart_data_parsing(char *data);

/*
    The buffer for each member must be bigger enough to store the parse value. If its size is not big, there will be problem of losing the value
    E.g:
    checksum[8] for 2 int values
    environment_humidity[9] for 2 int values and a '.' symbol
*/    
char dcd_header[1], id[8], checksum[8];
char environment_humidity[9], environment_temperature[9], soil_humidity[9], soil_temperature[9];

int main(){
    uart_data_parsing(value);

    write(STDOUT_FD, dcd_header, sizeof(dcd_header));
    printf("\n");

    write(STDOUT_FD, id, sizeof(id));
    printf("\n");

    write(STDOUT_FD, environment_humidity, sizeof(environment_humidity));
    printf("\n");

    write(STDOUT_FD, environment_temperature, sizeof(environment_temperature));
    printf("\n");

    write(STDOUT_FD, soil_humidity, sizeof(soil_humidity));
    printf("\n");

    write(STDOUT_FD, soil_temperature, sizeof(soil_temperature));
    printf("\n");

    write(STDOUT_FD, checksum, sizeof(checksum));
    printf("\n");
}

void uart_data_parsing(char *data){
    union data_frame {
        struct data {
            char dcd_header[1];
            char id[2];
            char environment_humidity[2];
            char environment_temperature[2];
            char soil_humidity[2];
            char soil_temperature[2];
            char checksum[1];
        } data;
        char data_storage[12];
    } frame;

    // For char array with hex value, using strcpy() will result in error
    memcpy(frame.data_storage, data, 12);

    //dcd_header parsing
    sprintf(dcd_header, "%c", frame.data.dcd_header[0]);

    //id parsing
    if (frame.data.id[0] < 10) sprintf(id, "0%d", frame.data.id[0]);
    else sprintf(id, "%d", frame.data.id[0]);

    if (frame.data.id[1] < 10) sprintf(id, "%s0%d", id, frame.data.id[1]);
    else sprintf(id, "%s%d", id, frame.data.id[1]);

    //environment_humidity parsing
    if (frame.data.environment_humidity[0] < 10) sprintf(environment_humidity, "0%d", frame.data.environment_humidity[0]);
    else sprintf(environment_humidity, "%d", frame.data.environment_humidity[0]);

    if (frame.data.environment_humidity[1] < 10) sprintf(environment_humidity, "%s.0%d", environment_humidity, frame.data.environment_humidity[1]);
    else sprintf(environment_humidity, "%s.%d", environment_humidity, frame.data.environment_humidity[1]);

    //environment_temperature parsing
    if (frame.data.environment_temperature[0] < 10) sprintf(environment_temperature, "0%d", frame.data.environment_temperature[0]);
    else sprintf(environment_temperature, "%d", frame.data.environment_temperature[0]);

    if (frame.data.environment_temperature[1] < 10) sprintf(environment_temperature, "%s.0%d", environment_temperature, frame.data.environment_temperature[1]);
    else sprintf(environment_temperature, "%s.%d", environment_temperature, frame.data.environment_temperature[1]);

    //soil_humidity parsing
    if (frame.data.soil_humidity[0] < 10) sprintf(soil_humidity, "0%d", frame.data.soil_humidity[0]);
    else sprintf(soil_humidity, "%d", frame.data.soil_humidity[0]);

    if (frame.data.soil_humidity[1] < 10) sprintf(soil_humidity, "%s.0%d", soil_humidity, frame.data.soil_humidity[1]);
    else sprintf(soil_humidity, "%s.%d", soil_humidity, frame.data.soil_humidity[1]);

    //soil_temperature parsing
    if (frame.data.soil_temperature[0] < 10) sprintf(soil_temperature, "0%d", frame.data.soil_temperature[0]);
    else sprintf(soil_temperature, "%d", frame.data.soil_temperature[0]);

    if (frame.data.soil_temperature[1] < 10) sprintf(soil_temperature, "%s.0%d", soil_temperature, frame.data.soil_temperature[1]);
    else sprintf(soil_temperature, "%s.%d", soil_temperature, frame.data.soil_temperature[1]);

    // checksum parsing
    sprintf(checksum, "%x", frame.data.checksum[0]);
}
```
**Note**: For not using ``printf()`` and ``write()`` function to display the result, set up debug with GDB to watch the variable. Parsed variables like ``dcd_header[1]``, ``id[8]``, ``checksum[8]``,... must be declared as local variable inside ``uart_data_parsing()`` for ``Watch`` in GDB.