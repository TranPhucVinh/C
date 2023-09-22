# Union packing 4 8-bit int numbers to a 32-bit number
```cpp
#include <stdio.h>
#include <stdint.h>

union ipv4 {
	struct {
		uint8_t a;
		uint8_t b;
		uint8_t c;
		uint8_t d;
	} bytes;
	uint32_t int32;
};

int main( int argc, char ** argv ) {
	union ipv4 addr;
	addr.bytes = { 192, 168, 0, 96 };
	printf("%d.%d.%d.%d - (%d)\n", addr.bytes.a, addr.bytes.b, addr.bytes.c, addr.bytes.d, addr.int32);//192.168.0.96 - (1610655936)
	return 0;
}
```
**Explain**:
```
1100000000000001010100011000000 = 1610655936 = 0b1100000 (0d96). 00000000 (0d0). 10101000 (0d168). 11000000 (0d192)
```
# Parse a char array into 3 smaller char array

Using ``struct`` inside ``union`` to split a string with the following sequence ``id``,  ``command`` and ``check_sum``.

E.g: ``12345`` has ``id`` is ``1``, ``command`` is ``234`` and ``check_sum`` is ``5``.

## Program

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
**Note**: Using ``printf()`` like this will cause error:

```c
printf("%s\n", frame.data.id);//12345
printf("%s\n", frame.data.command);//2345
printf("%s\n", frame.data.check_sum);//5
```

## Setting up value for parsing

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT_FD 1

char value[] = "12345";
char id[1];
char command[3];
char check_sum[1];

//Other declaration like program above

int main(){
    union data_frame frame;

    strcpy(frame.data_storage, value);

    strcpy(id, frame.data.id);
	strcpy(command, frame.data.command);
	strcpy(check_sum, frame.data.check_sum);

	write(STDOUT_FD, id, sizeof(id));
    printf("\n");

	write(STDOUT_FD, command, sizeof(command));
    printf("\n");

	write(STDOUT_FD, check_sum, sizeof(check_sum));
    printf("\n");
}
```
Compile with ``GCC``:

```
(NULL)
234
5
```
Compile with ``G++``:

```
1
234
5
```

The problem with GCC happens with ``sprintf()``:

```c
sprintf(id, "%s", frame.data.id);
```

**Problem solved**: Declare ``static`` for all variable used to parse (even when they are global or local variable in other examples)

```c
static char id[1];
static char command[3];
static char check_sum[1];
```

However using ``static`` is not actuall prefered. Converting string to hex value for later parsing, check **Example 2**.

# Parse a char array into smaller chars and numbers

Parsing a char array into the following fields

Char array: ``0x24 0x00 0x01 0x1A 0x05 0x1F 0x20 0x2F 0x1C 0x17 0x20 0x61``

* DCD header: ``$`` (``0x24``)
* ID: ``0001`` (``0x00`` ``0x01``)
* Environment humidity: ``26,05`` (``0x1A`` ``0x05``)
* Environment temperature: ``31,32``(``0x1F`` ``0x20``)
* Soil humidity: ``47,28`` (``0x2F`` ``0x1C``)
* Soil temperature: ``23,32`` (``0x17`` ``0x20``)
* Checksum: 0x61 (OR 11 bytes give 0x0261, 0x61 is the lower byte)

Program: [union_string_parsing.c](union_string_parsing.c)

**Note**: For not using ``printf()`` and ``write()`` function to display the result, set up debug with GDB to watch the variable. Parsed variables like ``dcd_header[1]``, ``id[8]``, ``checksum[8]``,... must be declared as local variable inside ``union_string_parsing()`` for ``Watch`` in GDB.
