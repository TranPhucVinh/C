### Very basic

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

### get and set

```c
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

```c
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
=> The constructor will print out automatically after object is being declared ``Name name``

### Set variable in constructor

```c
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

### More than 1 constructor in one Class

```c
#include <iostream>

using namespace std;

class Name{
	public:
	Name(){
		name = "Learning C++ sadas \n";
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