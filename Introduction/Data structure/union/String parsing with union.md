Using ``struct`` inside ``union`` to split a string with the following sequence ``id``,  ``command`` and ``check_sum``.

E.g: ``12345`` has ``id`` is ``1``, ``command`` is ``234`` and ``check_sum`` is ``5``.

### Program

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <unistd.h>
#include <string.h>

#define STDOUT_FD 1

extern "C" {
   void app_main();
}

char displayedString[] = "12345";

void displayString(void *pvParam);

void app_main()
{
    xTaskCreate(displayString, "Display string", 2048, NULL, 1, NULL);
}

void displayString(void *pvParam){
    union data_frame {
        struct data {
            char id[1];
            char command[3];
            char check_sum[1];
        } data;
        char data_storage[5];
    };

	union data_frame frame;

  	while(1){
		strcpy(frame.data_storage, displayedString);

		write(STDOUT_FD, frame.data.id, sizeof(frame.data.id)); //1
		printf("\n");
		write(STDOUT_FD, frame.data.command, sizeof(frame.data.command));//234
		printf("\n");
		write(STDOUT_FD, frame.data.check_sum, sizeof(frame.data.check_sum));//5
		printf("\n");

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
  vTaskDelete(NULL);
}
```
**Note**: Using ``printf()`` like this will cause error:

```c
printf("%s\n", frame.data.id);//12345
printf("%s\n", frame.data.command);//2345
printf("%s\n", frame.data.check_sum);//5
```

### Setting up value for parsing

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