## if ... else

```c
#include <iostream>

using namespace std;
int a;
main(){
cout << "Enter value of a: ";
cin >> a;
	if (a == 6)
	{
		cout << "value = 6";
	}
	else 
	{
		cout <<  "value != 6";
	}
}
```

## switch case

```c
#include <iostream>

using namespace std;
int a;
main(){
cout << "Enter value of a: ";
cin >> a;
	switch (a)
	{	case 1:
		cout << "value = " << a;
		case 2:
		cout << "value = " << a;
		default:
		cout << " Default";
	}
}
```