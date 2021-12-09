### Example 1

Print out all files inside a folder with library ``dirent.h``

```c
#include <stdio.h>
#include <dirent.h>

int main(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir("."); //. for current folder
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}
```

### Example 2

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
