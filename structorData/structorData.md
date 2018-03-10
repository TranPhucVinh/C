### Workign with struct

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