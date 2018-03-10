Enter the value of each member in array then print out on screen.

```c++
#include <iostream>

using namespace std;
#include <stdio.h>

main() {
	int i, n, array[100];
	cout << "Enter the number of members: ";
	cin >> n;
	cout << "Enter the value of each member: ";
	for (i = 0; i < n; i++)
	{ 
		cin >> array[i];
	}
	for (i=0; i < n; i++)
	{
		cout << "Value of member " << i << " is " << array[i] <<endl;
	}
}
```

### Dynamic memory allocation

```c
#include <stdio.h>

main() {
	cout << "Enter the number of members: ";
	int n;
	cin >> n;
	int *dynamic = new int[n];
	for (int i = 0; i < n; i++){
		dynamic[i] = i;
		cout << dynamic[i] << "\n";
	}
}
```

After allocating, you have to terminate these dynamic memory so that the memory won't be leaked and the resources won't be wasted.

```c
#include <stdio.h>

main() {
	cout << "Enter the number of members: ";
	int n;
	cin >> n;
	int *dynamic = new int[n];
	for (int i = 0; i < n; i++){
		dynamic[i] = i;
		cout << dynamic[i] << "\n";
	}
}
delete[] dynamic;
```