
### Create new file

Create a file and add data to this file:

```c
#include <iostream>
#include <fstream>

using namespace std;

main() {
	
	ofstream myFile;
	myFile.open("text.txt");

	myFile << "I want Sophie Dee";

}
```