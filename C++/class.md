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