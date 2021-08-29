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