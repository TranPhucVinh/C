### **protect** method

``protected`` method are used for other class that inherited from main class.

### Example

Class **cloneNumberProcess** inherit from class **numberProcess**.

```cpp
#include <iostream>
using namespace std;

class numberProcess{
public:
	int addNumber(int a){
		addValue = a + 4;
		return addValue;
	}

protected: 
	int addValue;
};

class cloneNumberProcess: public numberProcess{
public:
	int addNumber(int a){
		addValue = a+30;
		return addValue;
	}
private: int addValue;
};

int main (){
	cloneNumberProcess classObject;

 	cout << "Result from inherited class is " << classObject.addNumber(90);
}
```

**Result**

```
Result from inherited class is 120
```

### Header files with class and public method

**header.h**

```cpp
#include <iostream>
using namespace std;

#ifndef integerValue
#define integerValue 190
#endif

class numberProcess{
public:
	int addNumber(int a);
	void unchanged();
};
```

**header.cpp**

```cpp
#include "header.h"

int numberProcess::addNumber(int a){
	return a + integerValue;
}

void numberProcess::unchanged(){
	cout << "hello world";
}
```

**main.cpp**

```cpp
#define integerValue 2000

#include "header.h"

class cloneNumberProcess: public numberProcess{
public:
	int addNumber(int a){
		return a+integerValue;
	}
};

int main (){
	cloneNumberProcess classObject;
	numberProcess numberProcessObject;
 	cout << "Result from cloneNumberProcess class is " << classObject.addNumber(90) << endl;
 	cout << "Result from numberProcess class is " << numberProcessObject.addNumber(90) << endl;
 	classObject.unchanged();
}
```
**Result**
```
Result from cloneNumberProcess class is 2090
Result from numberProcess class is 280
hello world
```