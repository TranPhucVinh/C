### Example 1

``struct`` inside a ``union``

```c
union data_frame {
    struct header {
        char id[1];
        char command[3];
        char check_sum[1];
    } header;//must give the name for struct header
    char data[5];
};

int main(){
    union data_frame data;

    strcpy(data.data, "12345");
    printf("data: %s\n", data.data);
    strcpy(data.header.id, "6");
	printf("header.id: %s\n", data.header.id);
    strcpy(data.header.command, "789");
	printf("header.command: %s\n", data.header.command);
    strcpy(data.header.check_sum, "0");
	printf("header.check_sum: %s\n", data.header.check_sum);
}
```
### Example 2

Split a string with the following sequence ``id``,  ``command`` and ``check_sum``

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