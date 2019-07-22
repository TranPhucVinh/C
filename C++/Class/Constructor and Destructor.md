## Introduction

```c++
#include <iostream>

using namespace std;

class helloWorld{
	public:
	void hello(){
		cout << "Hello World";
	}
};


main(){
	helloWorld hi;
	hi.hello();
}
```

**Result**

```
Hello World
```

### Constructor

A **class constructor** is a special member function of a class that is executed whenever we create new objects of that class.

```cpp
#include <iostream>

using namespace std;

class helloWorld{
	public:
	helloWorld(){
		cout << "hello world" << endl;
	}
};


main(){
	helloWorld hi;
}
```

**Result**

```
hello world
```

### Constructor with arguments

```cpp
#include <iostream>

using namespace std;

class helloWorld{
	public:
	helloWorld(){}
	helloWorld(int a, int b){
		c = a+b;	
	}
	void hello(){
		cout << "Hello World" << endl;
	}
	int getC(){
		return c;
	}
	private:
		int c;
};


main(){
	helloWorld hi;
	helloWorld helloWorldFunction(90, 13);
	hi.hello();
	cout << helloWorldFunction.getC() << endl;
}
```

```
Hello World
103
```

## get and set

```c++
#include <iostream>

using namespace std;

class Name{
	public:
	void setName(string id){
		name = id;
	}
	string getName(){
		return name;
	}
	private:
	string name;
};


main(){
	Name name;
	name.setName("Linux");
	cout << name.getName() << endl;
}
```
**Result**
```
Linux
```

### Constructor inside Class

```c++
#include <iostream>

using namespace std;

class Name{
	public:
	Name(){
		cout << "Learning C++ \n";
	}
	void setName(string id){
		name = id;
	}
	string getName(){
		return name;
	}
	private:
	string name;
};


main(){
	Name name;
	name.setName("Linux");
	cout << name.getName() << endl;
}
```

```
Learning C++
Linux
```

### Set variable in constructor

```c++
#include <iostream>

using namespace std;

class Name{
	public:
	Name(){
		name = "Learning C++ \n";
	}
	void setName(string id){
		name = id;
	}
	string getName(){
		return name;
	}
	private:
	string name;
};


main(){
	Name name;
	cout << name.getName() << endl;
}
```

```
Learning C++
```

### More than 1 constructor in one Class

```c++
#include <iostream>

using namespace std;

class Name{
	public:
	Name(){
		name = "Learning C++ \n";
	}
	Name (string system) {
		name = "Learn Linux Shell \n";
	}
	Name (int value){
		name = "Learn Node Js \n";
	}
	void setName(string id){
		name = id;
	}
	string getName(){
		return name;
	}
	private:
	string name;
};

main(){
	Name name;
	cout << name.getName() << endl;
	Name sys ("Free RTOS");
	cout << sys.getName() << endl;
	Name rtos(9);
	cout << rtos.getName() << endl;
}
```

```
Learning C++

Learn Linux Shell

Learn Node Js
```

### Destructor

A **destructor** is a special member function of a class that is executed whenever an object of it's class goes out of scope or whenever the delete expression is applied to a pointer to the object of that class.

```cpp
#include <iostream>

using namespace std;

class helloWorld{
	public:
	helloWorld(){
		cout << "hello world" << endl;
	}
	~helloWorld(){
		cout << "Object is being deleted" << endl;
	}
};


main(){
	helloWorld hi;
}
```

```
hello world
Object is being deleted
```
