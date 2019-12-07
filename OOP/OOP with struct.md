### struct in C

```c
#include <stdio.h>

struct student{
	int id;
	char name[50];
	char classroom[50];
};

main(){
	struct student erin = { 1977, " Erin", "Free Lancer" };
	printf("%s has id %d in class %s \n", erin.name, erin.id, erin.classroom);
}
```

**Result**

```
Erin has id 1977 in class Free Lancer 
```

### struct in C++

```c
#include <iostream>
using namespace std;

struct student {
	int id;
	string name;
	string classroom;
};

main() {
	struct student erin = { 1977, " Erin", "Free Lancer" };
	cout << erin.name << " " << erin.id << " " << erin.classroom << endl;
}
```

**Result**
```
Erin 1977 Free Lancer
```

### Object from struct

```c
#include <stdio.h>

struct student{
	int id;
	char name[50];
	char class[50];
} student1;

main(){
	strcpy(student1.name, "Jayne"); //to set variable with char in struct
	student1.id = 1986;
	strcpy(student1.class, "Free Lancer");
	printf(" %s has id %d in class %s ", student1.name, student1.id, student1.class);
}
```

```
Jayne has id 1986 in class Free Lancer
```
### Missing the line in code

```c
#include <stdio.h>
#include <string.h>

struct student {
	int id;
	char name[50];
	char class[50];
} student1;

main(){
	printf("Enter ID: ");
	scanf("%d", &student1.id);
	printf("Enter name: ");
	scanf("%s", &student1.name);
	printf("Enter class: ");
	scanf("%s", &student1.class);
	printf(" %s has id %d in class %s ", student1.name, student1.id, student1.class);
}
```

Change ``char name[50]`` to ``char* name``