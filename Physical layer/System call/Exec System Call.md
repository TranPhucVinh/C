These ``exec`` system call are basically used to run a system command in a separate process

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

```c
int execlp(const char *file, const char *arg, ..., NULL );
```

E.g:

```c
execlp("ping", "ping", "google.com", NULL);
```