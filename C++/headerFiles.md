To compile cpp file with mupltiples header files

```
g++ -o outputFile main.cpp other.cpp etc.cpp
```

### BASIC

``header.h``

```c
#include <iostream>
using namespace std; // this line is optional

void helloworld();
```

``header.cpp``

```c
#include <iostream>
#include "header.h"
using namespace std; // this line is optional

void helloworld(){
	cout << "Hello, World!" << endl;
}
```

``test.cpp``

```c
#include <iostream>
#include "header.h" //"header.h", not <header.h>

using namespace std;

int main(){
	helloworld();
}
```

#### Result

```
Hello, World!
```

### WITH CLASS

``header.h``

```c
#include <iostream>
#ifndef header_h
#define header_h
using namespace std;

class Header
{
  public:
    void display();
    void displayNumber(int number);
    void displayRespective(int lastNumber);
  private:
    int _number;
    int _lastNumber;
};

void helloworld();

#endif
```

Notice

```
#ifndef header_h
#define header_h
```
Without this line, there will be error when calling class Header in header.cpp

``header.cpp``

```c
#include <iostream>
#include "header.h"
using namespace std;

void Header::display(){
	cout << "Hello, World!" << endl;
}

void Header::displayNumber(int number){
	_number = number;
	cout << "This number is " << _number << endl;
}

void Header::displayRespective(int lastNumber){
	_lastNumber = lastNumber;
	int i;
	for (i = 0; i < _lastNumber; i++){
		cout << i << endl;
	}
}

void helloworld(){
	cout << "Hello, World!" << endl;
}
```

``test.cpp``

```c
#include <iostream>
#include "header.h" //"header.h", not <header.h>

using namespace std;

int main(){
	Header header;
	header.display();
	header.displayNumber(6);
	header.displayRespective(6);
	helloworld();
}
```

```
Hello, World!
This number is 6
0
1
2
3
4
5
Hello, World!
```
