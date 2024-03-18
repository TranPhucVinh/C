# [Char array as string](Char%20array%20as%20string.md)

* [Define](Char%20array%20as%20string.md#define)
* [Get size of string char](Char%20array%20as%20string.md#get-size-of-string-char)
* [Char array as argument in function](Char%20array%20as%20string.md#char-array-as-argument-in-function)
* [Overflow a char buffer as string](Char%20array%20as%20string.md#overflow-a-char-buffer-as-string)

# [Char pointer as string](Char%20pointer%20as%20string.md)
* [Define](Char%20pointer%20as%20string.md#define)
* [Change value](Char%20pointer%20as%20string.md#change-value)
* [Char pointer as argument in function](Char%20pointer%20as%20string.md#char-pointer-as-argument-in-function)
* [Function returns a string](Char%20pointer%20as%20string.md#function-returns-a-string)

[Char pointer array](../Array/Two%20dimension%20array%20on%20heap%20memory.md#create-a-char-pointer-with-row-stored-on-stack-memory-and-column-stored-on-heap-memory): Strings as array member

```c
char *string_array[3] = {"string 1", "string 2", "string 3"};
```
There is no built-in functions or specific method in C to get the total member of a [char pointer array](../Array/Two%20dimension%20array%20on%20heap%20memory.md#create-a-char-pointer-with-row-stored-on-stack-memory-and-column-stored-on-heap-memory) or [a double pointer](../../Physical%20layer/Memory/Pointer/Pointer%20to%20pointer.md) char.

# API
## [String copy](API/String%20copy.md)

* [sprintf()](API/String%20copy.md#sprintf)
* [snprintf()](API/String%20copy.md#snprintf)
* [strcpy()](API/String%20copy.md#strcpy)
* [strncpy()](API/String%20copy.md#strncpy)
* [strdup()](API/String%20copy.md#strdup)
* [bcopy()](API/String%20copy.md#bcopy)

## [String append](API/String%20append.md)

* [atoi()](#String%20append.md#atoi): Convert a string integer to integer (**itoa()** isn't supported)
* [strrev()](#String%20append.md#strrev): Reverse string
* [strcat()](#String%20append.md#strcat), [strncat()](String%20append%20functions.md#strncat)
* [Dynamically append a char pointer as string](String%20append%20functions.md#dynamically-append-a-char-pointer-as-string) by [malloc()](../../Physical%20layer/Memory/Dynamic%20memory%20allocation/API.md#malloc)

## [String parsing](API/String%20parsing.md)

* [strtok()](#strtok): Split string by delimiters
* [strtol()](#strtol): Split number and character from a string then convert that number to long; same with [strtoul()](#strtoul) as number is converted to unsigned long
* [strstr()](#strstr): Find a substring inside a string
* [tolower()](API/String%20parsing.md#tolower): Convert upcase to lowercase

[strstr() examples](API/strstr()%20examples.md):
* Find a first part and second part of a string splitted by a substring
* Split a string by substring
* Replace substring inside a string
* Split string with \x0a; applied this for kmess

## [String remove](String%20remove%20examples.md)

* [Remove garbage value of a string](String%20remove%20examples.md#remove-garbage-value-of-a-string)
* [Remove a specific character from a string](String%20remove%20examples.md#remove-a-specific-character-from-a-string), [remove the first character from a string](String%20remove%20examples.md#remove-the-first-character-from-a-string)
* [Remove a character from a string with specified index](String%20remove%20examples.md#remove-a-character-from-a-string-with-specified-index)
