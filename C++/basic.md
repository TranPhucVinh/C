### Hello, World!
```cpp
#include <iostream>

using namespace std;

void main(){
	cout << "Hello, World!" << endl;
}
```

``\n`` and ``endl`` is the same.
``endl: endline``

g++ compiler need main() to be int. so ``int main()`` or just simply ``main()``

### Type in - print out

```c
#include <iostream>

using namespace std;

main(){
	int age;
	cout << " how old are you ? \n";
	cin >> age;
	cout << age << endl;
}
```

### Type in: Many arguments

```c
#include <iostream>

using namespace std;

main(){
	int age, year, day, month;
	cout << " how old are you ? \n";
	cin >> age >> day >> year >> month;
	cout << age << " " << day << " " << year << " " << month << " " << endl;
}
```

### string

```c
#include <iostream>

using namespace std;

main(){
	string sentence;
	cin >> sentence;
	cout << "The whole sentence is: " << sentence;
}
```

**Result**

### display the whole string

```c
#include <iostream>

using namespace std;

main(){
	string sentence;
	cout<< "what is your sentence ? \n";
	getline(cin, sentence);
	cout << "The whole sentence is: " << sentence;
}
```
### Problem with getline()

```c
#include <iostream>

using namespace std;

main(){
	int age;
	cout << "enter age: ";
	cin >> age;
	cout << age;
	string sentence;
	cout<< "what is your sentence ? \n";
	getline(cin, sentence);
	cout << "The whole sentence is: " << sentence;
}
```

After entering the value of ``age`` and press enter, ``age`` value will appear then the programm stop as after entering "ENTER", this will be in buffer then getline will stop as knowing that ENTER has been pressed.

### if ... else

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

### switch case

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