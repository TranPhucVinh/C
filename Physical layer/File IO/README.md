* [stdio](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/stdio)
* [File I/O system call](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call)
* [FIFO](FIFO)
* [stat](#stat)
* [uio](uio)

# stat

## API

```c
#include <sys/stat.h>
int stat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
```

``stat()`` runs normally on Git Bash and Command Prompt.

### struct stat

```c
struct stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    /* Since Linux 2.6, the kernel supports nanosecond
        precision for the following timestamp fields.
        For the details before Linux 2.6, see NOTES. */

    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */

#define st_atime st_atim.tv_sec      /* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
```

**Return**: On success, ``0`` is returned.  On error, ``-1`` is returned, and errno is set appropriately.

## Examples

Enter filename then print out the information about a file such as inode, file type, user ID,...

### stat()

```c
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	struct stat statBuffer;
    char filePath[] = "test.c";

    if (!stat(filePath, &statBuffer)){
		printf("ID of device containing file st_dev: %ld\n", statBuffer.st_dev);
		printf("Inode number st_ino: %ld\n", statBuffer.st_ino);
        printf("Mode of file: %o\n", statBuffer.st_mode);//View file type + file permission under octal
	} else {
		puts("File not exist");
	}
}		
```

For file type + file permission, if it returns:

```
Mode of file: 100777
```

``777`` are file permission for owner, group and others

``100000`` stands for regular file type

```c
#define	__S_IFREG	0100000	/* Regular file.  */
```

### fstat()

```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	struct stat statBuffer;

	char filePath[] = "test.c";
    int fileDescription = open(filePath, O_RDONLY);//Open test.txt
    fstat(fileDescription, &statBuffer);

    printf("ID of device containing file st_dev: %ld\n", statBuffer.st_dev);
    printf("Inode number st_ino: %ld\n", statBuffer.st_ino);
}	
```