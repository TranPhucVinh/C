# API

* [stdin and stdout API](stdin%20and%20stdout.md)
* [File pointer API](File%20pointer%20API.md)

## Other API

### rename()

Rename a file

```c
int rename(const char *old_filename, const char *new_filename)
```

**Return**: ``0`` if rename successfully, ``1`` if unable to rename file

### remove()

Remove a file

```c
int remove(const char *filename);
```

### perror()

Print out message describe error in ``stderr``.

```c
void perror(const char *str)
```

**Example**

```c
int main() {
	perror("hello"); //hello: Success
}
```

**Example: No such file or directory**

```c
int main() {
	FILE *file;
	file = fopen("text.abc", "r");
	if (file == NULL) {
		perror("Error");//Error: No such file or directory
	}
}
```

### Examples

* [stdio examples](stdio%20examples.md)
* [File pointer examples](File%20pointer%20examples.md)