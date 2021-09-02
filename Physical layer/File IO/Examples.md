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

Enter filename then print out the information about a file such as inode, file type, user ID,...

```c
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	struct stat statBuffer;

	if (argc != 2) {
		puts("You haven't entered enough parameter to execute\n");
        return 0;
	}

	if (!stat(argv[1], &statBuffer)){
		printf("ID of device containing file st_dev: %ld\n", statBuffer.st_dev);
		printf("Inode number st_ino: %ld\n", statBuffer.st_ino);
	} else {
		puts("File not exist");
	}
}	
```
### Example 3

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