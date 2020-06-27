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
	printf("%s has id %d in class %s \n", erin.name, erin.id, erin.classroom); //Erin has id 1977 in class Free Lancer 
}
```

**Size**: ``struct`` has the size of its all data member

Example:

```c
struct student erin = { 1977, " Erin", "Free Lancer" };
printf("size %d", sizeof(erin)); //104
```

Size ``104 = name[50] + classroom[50] + id (int)``

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
	cout << erin.name << " " << erin.id << " " << erin.classroom << endl; //Erin 1977 Free Lancer
}
```

### Object from struct

```c
#include <stdio.h>
#include <string.h> // for strcpy

struct student{
	int id;
	char name[50];
	char job[50];
} student1;

main(){
	strcpy(student1.name, "Jayne"); //to set variable with char in struct
	student1.id = 1986;
	strcpy(student1.job, "Free Lancer");
	printf(" %s has id %d with job %s \n", student1.name, student1.id, student1.job);
}
```

```
Jayne has id 1986 with job Free Lancer 
```

### Enter value for struct

```cpp
#include <stdio.h>
#include <string.h>

struct student {
	int id;
	char name[50];
	char job[50];
} student1;

main(){
	printf("Enter ID: ");
	scanf("%d", &student1.id);
	getc(stdin); //To handle with issue scanf before fgets

	printf("Enter name: ");
	fgets(student1.name, 50, stdin); //fgets allow to enter value with space

	//fgets() newline handler
	int len=strlen(student1.name);
	if(student1.name[len-1]=='\n')	student1.name[len-1]='\0';

	printf("Enter job: ");
	scanf("%s", student1.job);
	printf("%s has id %d with job %s \n", student1.name, student1.id, student1.job);
}	
```