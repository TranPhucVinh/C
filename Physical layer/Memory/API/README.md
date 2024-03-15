# memcpy()

Copy n bytes from memory area ``str2`` to memory area ``str1``.

```c
void *memcpy(void *str1, const void *str2, size_t n)
```
``memcpy()`` in static memory
```c
const char src[50] = "Hello, World!";
char dest[50];
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```
``memcpy()`` in dynamic memory
```c
const char *src = "Hello, World!";
char *dest = (char *) malloc(15);
memcpy(dest, src, strlen(src)+1);
printf("String: %s\n", dest); //String: Hello, World!
```
``memcpy()`` from dynamic memory to static memory
```c
char src[50] = "Hello, World !";
char *dest;
dest = (char*)malloc(sizeof(src)*sizeof(char));
memcpy(dest, src, sizeof(src));
printf("String: %s\n", dest); //String: Hello, World!
```
``memcpy()`` in specific position

```c
char *dest = (char *) malloc(15);
memcpy(dest, "123", 3);
printf("String: %s\n", dest);//String: 123
memcpy(dest+1, "456", 3);
printf("String: %s\n", dest);//String: 1456
memcpy(dest+4, "456", 3);
printf("String: %s\n", dest);//String: 1456456

memcpy(dest+10, "456", 3);
/*
	String: 1456456 -> the string now is not appended after the previous appending as dest+10 
	result in discontinuous memory
*/
printf("String: %s\n", dest);
```

# memmove()

Like ``memcpy()``, ``memmove()`` copies n characters from memory area ``str2`` to memory area ``str1``.


```cpp
char str1[] = "Hello";
char str2[]  = "World";

printf("str1: %s, str %s\n", str1, str2);//str1: Hello, str World

/* Copies contents of str2 to sr1 */
memmove(str1, str2, sizeof(str2)); 

printf("str1: %s, str %s\n", str1, str2);//str1: World, str World
```
