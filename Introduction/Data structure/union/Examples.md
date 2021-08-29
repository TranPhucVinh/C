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

Program: ``union_string_parsing.c``

**Note**: For not using ``printf()`` and ``write()`` function to display the result, set up debug with GDB to watch the variable. Parsed variables like ``dcd_header[1]``, ``id[8]``, ``checksum[8]``,... must be declared as local variable inside ``union_string_parsing()`` for ``Watch`` in GDB.