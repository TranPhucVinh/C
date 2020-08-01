## printf()

```c
printf("%d ", a) // int
printf("%s ", a) // string
```

**Example**: ``printf("%s \n", "Hello, World!"); //Hello, World!``

**Return**: return the total print out character

```c
int returnPrintf = printf("Hello, World!\n");
printf("%d \n", returnPrintf); //14
```

## scanf()

``scanf()``: Read formatted input from ``stdin``

```c
int scanf ( const char * format, ... );
```

**Return**: number of items of the argument list successfully filled. This will return ``1`` (valid data enter) and ``0`` for invalid data enter.

**Example**: Enter ``int``, ``long`` (double), ``float`` variable

```c
scanf("%d", &a);    //int
scanf("%lf", &b);   //long
scanf("%f", &c);    //float
```

**Example**: Enter and print out ``char`` variable as ``integer`` number

```c
char a;
scanf("%c", &a);
printf("value: %c", a);
```

**Result**

    Enter 4 -> output 4
    Enter character a  -> output character a
    Enter abc -> output a

### Whitespace problem

```c
int a;
scanf("%d ", &a);
printf("%d", a);
```

You have to type value a; then type one more to finish command although the value of ``a`` is still printed out correctly. To print out the value of ``a`` just after typing it, delete the space after ``%d``.

### Print out a string as char variable

Because the array with ``char a[10]`` is a pointer so it doesn't need the pointer get value ``&`` in scanf.

```c
char a[10]; //10 character of string
scanf("%s", a);
printf("value: %s", a);
```

If you type in value with whitespace, like ``Hello, World!``, this will just print out only ``Hello,``.

### fgets()

To print out entered string included whitespace, using ``fgets()``: ``fgets(char *s, int n, FILE *stream)``

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin); 
printf("string is: %s\n", buf);
```

This will printout the entered string followed with a new line, to remove that new line:

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin); 
int len=strlen(buf); //where buff is your char array fgets is using
if(buf[len-1]=='\n')	buf[len-1]='\0';
printf("string is: %s\n", buf);
```

### Problem with scanf() before fgets()

As there is ``\n`` character goes after ``scanf()``, putting ``scanf()`` before ``fgets()`` will result in losing the ``fgets()`` command handler.