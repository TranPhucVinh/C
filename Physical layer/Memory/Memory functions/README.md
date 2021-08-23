### memcpy()

``memcpy()`` copies n characters from memory area ``str2`` to memory area ``str1``.

```c
void *memcpy(void *str1, const void *str2, size_t n)
```

Example with ``char[]`` (static memory)

```c
const char src[50] = "Hello, World!";
char dest[50];
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```
Example with ``*char`` (dynamic memory)
```c
const char *src = "Hello, World!";
char *dest = (char *) malloc(15);
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```

### memmove()

``memmove()`` copies a block of memory from a location to another.

```cpp
char str1[] = "Hello";  // Array of size 100 
char str2[]  = "World";  // Array of size 5 

puts("str1 before memmove "); 
puts(str1); //Hello

/* Copies contents of str2 to sr1 */
memmove(str1, str2, sizeof(str2)); 

puts("\nstr1 after memmove "); 
puts(str1); //World
```
