### Print out string

```cpp
#include <iostream>

using namespace std;

main(){
	cout << "Hello, World!" << endl;
}
```

``\n`` and ``endl`` is the same. ``endl: endline``

### Type in - print out

```cpp
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

```cpp
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

```cpp
#include <iostream>

using namespace std;

main(){
	string sentence;
	cin >> sentence;
	cout << "The whole sentence is: " << sentence;
}
```

### display the whole string

```cpp
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

```cpp
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

```cpp
#include <iostream>

using namespace std;

main(){
	int age;
	cout << "enter age: ";
	cin >> age;
	cout << age;
	string sentence;
	cout << "what is your sentence ? \n";
	cin.ignore(1); //ignore the last entering character, in this case is "ENTER"
	getline(cin, sentence);
	cout << "The whole sentence is: " << sentence;
}
```

### Simple dealing with input value

```cpp
#include <iostream>

using namespace std;
int age;
main(){
cout << "Your age ";
cin >> age;
cout << "The next 10 years: " << age + 10 <<"\n";
}
```

### cin.getline()

``cin.getline()`` allows you to enter a string which has white spaces too. 

Its syntax is as follows: ``cin.getline(name of string , size of the string);``

**Enter a string to a file**

```cpp
ofstream myFile("file.txt");
char data[111];
cin.getline(data, 100);
myFile << data;
myFile.close();
```

### setw()

```cpp
#include <iostream>
#include <iomanip> // io manipulation
using namespace std;

main() {
	cout << "Day  		Money \n"
	<< 	"---------------------------------\n";
	cout << 1 <<setw(18) << 1 << "\n";
	cout << 1 <<setw(18) << 1 << "\n";
	cout << 1987 <<setw(18) << 1977 << "\n";
}
```

**Result**

```
Day  		Money 
---------------------------------
1                 1
1                 1
1987          1977
```