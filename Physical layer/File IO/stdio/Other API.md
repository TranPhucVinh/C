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
