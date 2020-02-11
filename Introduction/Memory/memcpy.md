``memcpy()`` copies n characters from memory area str2 to memory area str1.

```c
void *memcpy(void *str1, const void *str2, size_t n)
```

**Example with char[]**

```c
const char src[50] = "Hello, World!";
char dest[50];
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```
**Example with char***
```c
const char *src = "Hello, World!";
char *dest = (char *) malloc(15); //A memory size must be given to *dest
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```
