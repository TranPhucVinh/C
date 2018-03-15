
### Create new file

``ofstream``: Outputting data to stream;

``ifstream``: input data from a file, means reading data from a file

Create a file and add data to this file:

```c
#include <iostream>
#include <fstream>

using namespace std;

main() {
	
	ofstream myFile;
	myFile.open("text.txt");

	myFile << "Hello, World";
	myFile.close();

}
```

One line of code

```c
ofstream myFile("file.txt");
```

**Check status:** is_open()

```c
include <iostream>
#include <fstream>

using namespace std;

main() {
	
	ofstream myFile("erin.txt");
	myFile << "Hello, World";
	if (myFile.is_open()){
		cout << "The file is open" << endl;
	}
	else cout <<"File is close !! \n";
	myFile.close();
	if (myFile.is_open()){
		cout << "The file is open" << endl;
	}
	else cout <<"File is close !! \n";
}
```

**Result**

```
The file is open
File is close !! 
```

### Entering data to txt file

```c
#include <iostream>
#include <fstream>

using namespace std;

main() {
	
	ofstream myFile("file.txt");
	cout << "Enter ID, Name, Money \n";
	int id;
	string name;
	double money;
	cin >> id >> name >> money;
	myFile << id << " " <<name << " " << money << endl;
	myFile.close();
}
```

### Read data from txt file

We have ``file.txt``

```
124 ertyewew 5666
```

File file.txt has 3 word; we create 3 variable word1, word2, word3 correspondingly to these 3 word

```c
#include <iostream>
#include <fstream>

using namespace std;

main() {
	
	ifstream myFile("file.txt");
	int word1;
	string word2;
	int word3;
	myFile >> word1 >> word2 >> word3;
	cout << word1 << " " <<  word2 << " " << word3;
	myFile.close();
}
```

**Result**

```
124 ertyewew 5666
```

### print out

we have file.txt

```
124 ertyewew 5666
1243 errtyewew 56666
12 edrtyewew 5666
```

```c
#include <iostream>
#include <fstream>

using namespace std;

main() {
	
	ifstream myFile("file.txt");
	int word1;
	string word2;
	int word3;
	while (myFile >> word1 >> word2 >> word3)
	{
		cout << word1 << " " <<  word2 << " " << word3 << endl;
	}
	myFile.close();
}
```

**Result**

```
124 ertyewew 5666
1243 errtyewew 56666
12 edrtyewew 5666
```

### Cursor in fstream

``fstream::tellg()`` tells the positon of the current cursor in ``get``

e.g

we have a file name ``file.txt``

```c
	ifstream myFile("file.txt");
	cout << myFile.tellg() << endl;
```

Result
```
0
```
(as at the beginning of the file)