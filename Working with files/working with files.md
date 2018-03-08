### fopen()

Used to open the file to read or write.

````c
FILE *file;
file = fopen("name of file to open to read", "<mode>");
````
**mode** include: 
```
* r
* w
* a
* r+
* w+
* a+
* t
* b
```
### fgets()

````c
fgets(char *s, int n, FILE *stream);
````
read the content in file "stream" until encounter the new line character ('\n') or until finished reading n-1 character; then store in "s".

````c
fgets(msg, 81, stream);
````

### fprintf()

stdout
```c
fprintf(stdout, "Hello, World! \n");
```
**Result**
```
Hello, World!
```

stderr
```c
fprintf(stderr, "Hello, World! \n");
```
**Result**
```
Hello, World!
```
(print out as red words in some compiler)
