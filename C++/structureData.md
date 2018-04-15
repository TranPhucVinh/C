### struct

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
	cout << erin.name << " " << erin.id << " " << erin.classroom;

}
```

**Result**
```
Erin 1977 Free Lancer
```
