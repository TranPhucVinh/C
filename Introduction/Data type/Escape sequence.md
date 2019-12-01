### Escape sequence

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
