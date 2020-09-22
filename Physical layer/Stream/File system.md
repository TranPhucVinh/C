### stat()

``stat()``: return information about a file, in the buffer pointed to by ``struct stat``.

``stat()`` runs normally on Git Bash and Command Prompt.

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

**Example**: Enter filename then print out the information about a file such as inode, file type, user ID,...

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