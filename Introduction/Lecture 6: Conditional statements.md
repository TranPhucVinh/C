# Command Line Arguments with main()

```c
int main( int argc, char *argv[] ){}
```

It is possible to pass **some values** from the command line to your C programs when they are executed. These values are called **command line arguments** and many times they are important for your program especially when you want to control your program from outside **instead of hard coding** those values inside the code.

The command line arguments are handled using **main()** function arguments where ``argc`` refers to the **number of arguments** passed, and ``argv[]`` is a **pointer array** which points to **each argument** passed to the program.

```c
int main( int argc, char *argv[] )  {
      printf("The argument supplied is %s and total argument is %d \n", argv[0], argc);
}
```

Compile ``g++ -o test test.c``

``./test``

**Result**

```
The argument supplied is ./test and total argument is 1 
```

## continue vs break

### break

```c
for (i=0; i<10; i++){
		if(i==5) break;
		printf("i value is %d \n", i);
	}
```

```
i value is 0 
i value is 1 
i value is 2 
i value is 3 
i value is 4 
```

### continue

```c
for (i=0; i<10; i++){
		if(i==5) continue;
		printf("i value is %d \n", i);
	}
```

```
i value is 0 
i value is 1 
i value is 2 
i value is 3 
i value is 4 
i value is 6 
i value is 7 
i value is 8 
i value is 9 
```

**Another example**

```c
int i = 0, a=0, b=0;
    while(i<10){
        i++;
        printf("i: %d \n", i);
		if(i==5) continue;
		a++;
		b++;
		printf("a: %d \n", a);
		printf("b: %d \n", b);
		printf("\n");
	}
```	

```
i: 1 
a: 1 
b: 1 

...

i: 4 
a: 4 
b: 4 

i: 5  //a++, b++ are bypass

i: 6 
a: 5 
b: 5 
...
i: 10 
a: 9 
b: 9 
```

### exit()

Exit the current process and return value **status** for the further process.

```c
void exit(int status) 
```
**E.g 1**

```c
int main(){
	printf("hello world \n");
	exit(0);
	for(int i=0; i<10; i++){
		printf("%d", i);
	}
}
```	

**Result**
```
hello world 
```
(the print out function in for loop is exit)

**E.g 2**

```c
int main(){
	for(int i=0;i<10;i++){
		printf("%d \n", i);
		exit(0);
	}
}
```

**Result** ``0``