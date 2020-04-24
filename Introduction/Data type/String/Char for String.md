### Error with string define

If define ``char *rawString = "This is Hello, World string"``, there will be an error ``segment core dump`` as you are trying to modify a string literal (defined by pointer).

### Print out a string with char[] and char*

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
char hello[] = "a character";
printf("%c \n", hello[3]); //h

char *returnChar = hello;
printf("returnChar[0]: %c \n", returnChar[0]); //returnChar[0]: h
```

**Get address of pointer char**
```c
printf("returnChar: %p \n", returnChar); //Address of returnChar is : 0x62FE30
```

### String as argument in function

```c
void printString(char hw[]){
	printf("%s ", hw);
}

void printStringPointer(char *hw){
	printf("%s ", hw);
}

int main(){
	printString("Hello, World \n"); //Hello, World
	printStringPointer("Hello, World \n"); //Hello, World
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
