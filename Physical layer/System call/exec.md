The ``exec`` system call are basically used to run a system command in a separate process
# execl()
```c
int execl(const char *path, const char *arg, ..., NULL);
```

``execl()`` takes the path of the executable binary file as the first and second argument. Then, the arguments that you want to pass to the executable followed by NULL.

```c
#include <stdio.h>
#include <unistd.h>

int main()  {
	execl("/bin/ping", "/bin/ping", "google.com", NULL);
}
```
# execlp()
```c
int execlp(const char *file, const char *arg, ..., NULL );
```

E.g:

```c
execlp("ping", "ping", "google.com", NULL);
```
# execv()
```c
int execv(const char *path, char *const argv[]);
```

``execv()`` has the same feature like ``execl()`` but takes all argument as the pointer array ``argv``

```c
char *command_array[] = {"/bin/ping", "google.com", NULL};
execv("/bin/ping", command_array);
```
# execvp()
```c
int execvp(const char *file, char *const argv[]);
```

``execvp()`` has the same feature like `` execlp()`` but takes all argument as the pointer array ``argv``. 

```c
char *command_array[] = {"ping", "google.com", NULL};
execvp("ping", command_array);
```
### return value

All ``exec`` system call only return value if it encounter error. Without error, the command inside all ``exec()`` system calls will execute the return value won't print out.

E.g:

```c
int exit_status = execlp("ls", "ls", NULL);//Result if ls command wil print out
printf("%d\n", exit_status);//This won't print out
```

Error command:
```c
int exit_status = execlp("lsa", "lsa", NULL);
printf("%d\n", exit_status);//-1
```
