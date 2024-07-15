# printf()

Sends formatted output to ``stdout``

```c
printf("%d ", a) // int
printf("%s ", a) // string
```

**Example**:  
```c
printf("%s \n", "Hello, World!"); //Hello, World!
```

**Return**: return the total print out character

```c
int returnPrintf = printf("Hello, World!\n");
printf("%d \n", returnPrintf); //14
```

**Use formated output in printf()**

```c
const char* string_output_format = "Displayed string: %s\n";
char displayedString[] = "Hello, World !";
printf(string_output_format, displayedString);       
```

**Percent symbol**: To use percent symbol, use ``%%``. E.g: ``printf("%d%%", 100);``
# %.*s

```c
void display_function(char *str, int str_len)
{
  printf("%.*s\n", str_len, str);
}

char *return_string(char *str, int str_len){
    char *returned_string = (char*) malloc(str_len + 1);
    sprintf(returned_string, "%.*s", str_len, str);
    return returned_string;
}

int main(){
    display_function("Hello, World !", 3);//Hel
    char *returned_string = return_string("Displayed string", 5);
    printf("%s\n", returned_string);//Displ
    free(returned_string);
}
```
# puts()

Writes a string to ``stdout`` followed with a new line

```c
int puts(const char *str)
```

```c
puts("hello"); //hello
```
## perror()

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