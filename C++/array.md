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