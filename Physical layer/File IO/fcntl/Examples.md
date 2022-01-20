Read entered data from the current running terminal (``/dev/tty``)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const char filePath[] = "/dev/tty";
char bufferRead[20];

int fileDescription;
void delaySeconds(long seconds);

int main(){
   fileDescription = open(filePath, O_RDONLY); //READ ONLY
   while(1){
	   bzero(bufferRead, sizeof(bufferRead));
      if(fileDescription < 0) return 1;
      else {
         read(fileDescription, bufferRead, sizeof(bufferRead));
         printf("%s", bufferRead);
      }
   }
    return 0;
}
```

Read data from USB port (``/dev/ttyUSB0``, ``/dev/ttyACM0``,...)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

const char filePath[] = "/dev/ttyACM0";
char bufferRead[20];

int fileDescription;
void delaySeconds(long seconds);

int main(){
   fileDescription = open(filePath, O_RDONLY); //READ ONLY
   while(1){
      if(fileDescription < 0) return 1;
      else {
         read(fileDescription, bufferRead, sizeof(bufferRead));
         printf("%s", bufferRead);
      }
      memset(bufferRead, 0, sizeof(bufferRead));
		delaySeconds(1);
   }
    return 0;
}

void delaySeconds(long seconds){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long totalSecond = 0;
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}
```
Write "H" and "L" to turn on, off LED in MCU connected to USB port (``/dev/ttyUSB0``, ``/dev/ttyACM0``,...)

```c
const char filePath[] = "/dev/ttyACM0";

int fileDescription;
void delaySeconds(long seconds);

int main(){
	fileDescription = open(filePath, O_WRONLY); //READ ONLY
	while(1){
		write(fileDescription, "H", sizeof("H"));
		delaySeconds(2);
		write(fileDescription, "L", sizeof("L"));
		delaySeconds(2);
	}
    return 0;
}
```
To write 0x12 and 0x34 to turn on, off LED:

```c
char turn_on[] = {0x12}, turn_off[] = {0x34};
write(fileDescription, turn_on, 1);
delaySeconds(1);
write(fileDescription, turn_off, 1);
delaySeconds(1);
```		
To write ``0x1234`` and ``0x5678`` to turn on, off LED:

```c
char turn_on[] = {0x12, 0x34}, turn_off[] = {0x56, 0x78};
write(fileDescription, turn_on, 2);
delaySeconds(1);
write(fileDescription, turn_off, 2);
delaySeconds(1);
```
