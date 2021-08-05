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
#include <stdlib.h>

int main(int argc, char *argv[]) {
	struct stat statBuffer;

	if (argc != 2) {
		puts("You haven't entered enough parameter to execute");
		exit(0);
	}

	if (!stat(argv[1], &statBuffer)){
		printf("ID of device containing file st_dev: %ld", statBuffer.st_dev);
		printf("Inode number st_ino: %ld", statBuffer.st_ino);
	} else {
		puts("File not exist");
	}
}	
```