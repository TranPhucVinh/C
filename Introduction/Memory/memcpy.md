``memcpy()`` copies n characters from memory area str2 to memory area str1.

```c
void *memcpy(void *str1, const void *str2, size_t n)
```

**Example**

```c
const char src[50] = "Hello, World!";
char dest[50];
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```
