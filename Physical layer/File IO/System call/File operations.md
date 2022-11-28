## Open a file to read

```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()

int fd;

int main(){
    char buffer[10];

    fd = open("test.md", O_RDONLY);
    
    read(fd, buffer, 10);
    puts(buffer);
}
```

To read a file send by ``<`` operator:

```c
int main(){
    char buffer[10];
    
    read(STDIN_FILENO, buffer, sizeof(buffer));
	write(STDOUT_FILENO, buffer, sizeof(buffer));
}
```
**Run**: ``./a.out < test.c``

To read a file from a specific index, like index ``10``, with ``lseek()``:

```c
int fd;
char buffer[10];

fd = open("README.md", O_RDONLY);
int offset = lseek(fd, 10, SEEK_SET);
printf("offset %d\n", offset);//10
if (offset > 0){
	read(fd, buffer, 10);
	printf("%s\n", buffer);
}
```

``lseek()`` is not available for stdin with ``/dev/tty``

``lseek(STDIN_FILENO, 10, SEEK_SET)`` will return ``-1`` for ``/dev/tty`` but will return a normal ``fd`` for  ``./a.out < test.c``.

``lseek()`` with [default character device](https://github.com/TranPhucVinh/C/blob/master/Kernel/Character%20device/create_character_device_by_seperated_operations.c) will return ``-1``.

## Read the whole file by chunk and dynamically store to a char pointer

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define READ_CHUNK_SIZE 3//This can be any >0 value

const char file_path[] = "README.md";
char temp_buffer[READ_CHUNK_SIZE];
char *file_buffer;
int fd;

void string_append(char **str, const char *str2);

int main(){
	fd = open(file_path, O_RDONLY);
	if(fd < 0) return 1;
	else {
		while(read(fd, temp_buffer, READ_CHUNK_SIZE)){
			string_append(&file_buffer, temp_buffer);
			//Clear buffer every time reading to avoid garbage value
			bzero(temp_buffer, READ_CHUNK_SIZE);
		}
		printf("\n");
	}
	close(fd);
	printf("%s", file_buffer);
    return 0;
}

void string_append(char **str, const char *str2) {
    char *tmp = NULL;

    // Reset *str
    if ( *str != NULL && str2 == NULL ) {
        free(*str);
        *str = NULL;
        return;
    }

    // Initial copy
    if (*str == NULL) {
        *str = (char*) malloc(strlen(str2)+1);
		bzero(*str, strlen(str2)+1);

        memcpy(*str, str2, strlen(str2));
    }
    else { // Append
        tmp = (char*) malloc(strlen(*str)+1);
		bzero(tmp, strlen(*str)+1);

        memcpy(tmp, *str, strlen(*str));
        *str = (char*) malloc(strlen(*str)+strlen(str2)+1);
		bzero(*str, strlen(*str)+strlen(str2)+1);

        memcpy(*str, tmp, strlen(tmp) );
        memcpy(*str + strlen(*str), str2, strlen(str2) );
        free(tmp);
    }
}
```

Simply print out the file content

```c
char buffer_read[READ_CHUNK_SIZE];
while(read(fd, buffer_read, READ_CHUNK_SIZE)){
        printf("%s", buffer_read);

        //Clear buffer every time reading to avoid garbage value
        bzero(buffer_read, READ_CHUNK_SIZE);
    }
    printf("\n");
```

## Open a file to write

```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()
#include <string.h> //for strlen()

int fd;

int main(){
    char buffer[] = "Hello, World !";

    fd = open("test.md", O_WRONLY);
    
    write(fd, buffer, strlen(buffer));
}
```