```c
struct student{
		int id;
		char name[50];
		char classroom[50];
};

int main() {
	struct student erin = { 1977, "Erin", "Free Lancer" };

	// printf("%d", sizeof(erin));
    memset(&erin, 0, 1);
    printf("value erin.id after: %d \n", erin.id);
    printf("value erin.name after: %s \n", erin.name);
    printf("value erin.classroom after: %s \n", erin.classroom);
}
```

```
value erin.id after: 1792 
value erin.name after: Erin 
value erin.classroom after: Free Lancer 
```

```
1977 = 0000 0111 1011 1001
1792 = 111 0000 0000
```

The right 1 byte of 1977 is replace with 0

```c
memset(&erin, 0, 2);
```

```
value erin.id after: 0 
value erin.name after: Erin 
value erin.classroom after: Free Lancer 
```

```c
memset(&erin, 0, 5);
```

```
value erin.id after: 0 
value erin.name after:  
value erin.classroom after: Free Lancer 
```

```c
memset(&erin, 0, 54);
```

```
value erin.id after: 0 
value erin.name after:  
value erin.classroom after: Free Lancer 
```

```c
memset(&erin, 0, 55);
```

```
value erin.id after: 0 
value erin.name after:  
value erin.classroom after: 
```