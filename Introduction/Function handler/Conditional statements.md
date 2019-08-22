## return

The **return statement** stops the execution of a function and returns a value from that function.

Return in **void**

```c
void returnNumber(){
	int a = 0, b=0;

	if ((a==0)&&(b==0)){
	 	return;
	 }
	printf("inside \n");
}

int main() {
	returnNumber();
	printf("hello world");
}
```

**Result**

```
hello world
```

If ``a==0`` and ``b==0``, it return in ``void returnNumber()`` and end the function.

If we ommitted ``if ((a==0)&&(b==0))``, the result will be

```
inside
hello world
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

## exit()

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
