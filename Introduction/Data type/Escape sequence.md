### Escape sequence

**New line**

```c
printf("Hello,%cworld!", 0x0a);
```

```
Hello,
world!
```

New line ``LF`` (line feed) has ASCII code ``0x0a``

The escape sequence ``\n`` does not stand for a backslash followed by the letter n, because the backslash causes an "escape" from the normal way characters are interpreted by the compiler. After seeing the backslash, the compiler expects another character to complete the escape sequence, and then translates the escape sequence into the bytes it is intended to represent. 

### ASCII code with escape symbol

```c
printf("ASCII value: %d \n", '\\');
```

```
ASCII value: 92 
```

(``\`` has ASCII code 92)

From this, it can be seen that ``\`` is an escape symbol.

```c
printf("ASCII value: %d \n", ']'); //93
printf("ASCII value: %d \n", '\]'); // 93
```

**Normal character**

```c
printf("ASCII value: %d \n", 'c'); //99
printf("ASCII value: %d \n", '\c'); //99
```
ASCII value: 99 

However, there are special value that goes with escape sequence:

| Escape sequence | Hex value in ASCII|Character represent|
| ------- |------|------|
|\a |07|Alert (Beep, Bell) (added in C89)|		
|\b |08|Backspace|			
|\e |1B|Escape character|
|\f	|0C|Formfeed Page Break|
|\n	|0A|Newline (Line Feed)|
|\r	|0D|Carriage Return|
|\t	|09|Horizontal Tab|
|\v	|0B|Vertical Tab|
|\\	|5C	|Backslash|
|\'	|27	|Apostrophe or single quotation mark|
|\"	|22	|Double quotation mark|
|\?	|3F	|Question mark (used to avoid trigraphs)|
|\nnn|	any|	The byte whose numerical value is given by nnn interpreted as an octal number|
|\xhh…|	any|	The byte whose numerical value is given by hh… interpreted as a hexadecimal number|
|\uhhhh|none|	Unicode code point below 10000 hexadecimal|
\Uhhhhhhhh|	none|	Unicode code point where h is a hexadecimal digit|

```c
printf("ASCII value: %d \n", 'a');//97
printf("ASCII value: %d \n", '\a');//7
```

### char type and escape sequence

```c
printf("Char value: %c \n", '\\'); //Char value: \
printf("Char value: %c \n", '\a'); // Char value: 
```

```c
printf("b: %c \n", '\0');
```

```
b:  
```

### Escape sequence: octal vs decimal

```c
printf("ASCII value: %d \n", '\10');
```

**Result**

```
ASCII value: 8 
```

C compiler will understand that the passed-in value after escape sequencer ``\`` is a octal number (Octal value ``10`` has decimal value ``8``)

### Other escape sequences

``'\0'``: null

```c
int main() {
	char a = 0;
	char b = '\0';
	printf("b: %d and a: %d \n", b, a);
}
```
**Result**

```
b: 0 and a: 0 
```

With:

```c
char b = '\1'; //b: 1
```

```c
char b = '\2'; //b: 2
```

```c
char b = '\6'; //b: 6
```

```c
char b = '\12'; //b: 10
```

### Problem with data type

```c
printf("b: %d \n", '\a');
```

```
b: 7 
```

```c
printf("b: %d \n", '\aasd');
```

```
b: 123827044 
```
