### Print out a string with char[] and pointer

```c
char hw[] = "Hello, World!";
char *pointerString = "Pointer String";
printf("%s \n", hw); //Hello, World! 
printf("%s \n", pointerString); //Pointer String 
```
**Print out with index**
```c
char helloWorld[] = "Hello world 10 times";
printf("%s \n",helloWorld+3); //lo world 10 times
```

### Get a character in a string

```c
int main() {
    int i;
    char hello[] = "a character";
    printf("%c \n", hello[3]); //h
    return 0;
}
```

### String as argument in function

```c
void printString(char hw[]){
	printf("%s ", hw);
}

int main(){
	printString("Hello, World \n"); //Hello, World
}
```

### strlen()

``size_t strlen(const char *)``: Return length of a string

```c
char stringSize[] = "Hello, World!";
char *pointerString = "Pointer string";

//%ld for size_t as long unsignee int
printf("%ld", strlen(stringSize)); //13
printf("%ld", strlen(pointerString)); //14
```
