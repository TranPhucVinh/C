### Print out a string with char

```c
char hw[] = "Hello, World!";
printf("%s ", hw);
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

```c
char stringSize[] = "Hello, World!";
printf("%d", strlen(stringSize)); //13
```