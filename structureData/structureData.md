## Working with struct

### Basic

```c
#include <stdio.h>

struct student {
	int id;
	char name[50];
	char class[50];
};

main()
{
struct student erin = { 1977, " Erin", "Free Lancer" };
printf(" %s has id %d in class %s ", erin.name, erin.id, erin.class);
}
```

**Result**

```
Erin has id 1977 in class Free Lancer 
```

### Other

```c
#include <stdio.h>

struct student {
	int id;
	char name[50];
	char class[50];
} student1;

main()
{
	strcpy(student1.name, "Jayne"); //to set variable with char in struct
	student1.id = 1986;
	strcpy(student1.class, "Free Lancer");
	printf(" %s has id %d in class %s ", student1.name, student1.id, student1.class);
}
```

```
Jayne has id 1986 in class Free Lancer
```
