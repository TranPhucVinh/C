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
**Example**: Remove the first character of a string

```c
char displayedString[] = "1Hello, World !";
void firstCharRemove(char *modifiedString);

int main(){
  printf("%s\n", displayedString);
  firstCharRemove(displayedString);
  printf("%s\n", displayedString);
}

void firstCharRemove(char *modifiedString){
	//remove character "1"
	if (modifiedString[0] == '1') memmove(modifiedString, modifiedString+1, strlen(modifiedString));
}
```
