# Count total duplicate numbers inside a sorted array

```c
#include <stdio.h>

int arr[] = {5, 7, 9, 9, 10, 11, 13, 13, 13, 16};
int hash_table[17];

void main(void)
{
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++){
        hash_table[arr[i]] += 1; 
    }

    for (int i = 0; i < 17; i++){
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}
```
# Count total duplicate string numbers inside a string

```cpp
string num = "1210";
std::sort(num.begin(), num.end());

int sz = num[num.size() - 1] - 48 + 1;// Value of the biggest string number, i.e "2" + 1
cout << sz << endl;
int hash_table[sz];

for (int i = 0; i < sz; i++){
    hash_table[i] = 0;
}

for (int i = 0; i < num.size(); i++){
    hash_table[num[i] - 48] += 1; 
}

for (int i = 0; i < sz; i++){
    printf("%d ", hash_table[i]);
}
```
# Check if number has equal digit count and digit value (Leetcode 2283):

E.g 1: num = "1210"
* Output: true
* Explanation:
    * num[0] = '1'. The digit 0 occurs once in num.
    * num[1] = '2'. The digit 1 occurs twice in num.
    * num[2] = '1'. The digit 2 occurs once in num.
    * num[3] = '0'. The digit 3 occurs zero times in num.

E.g 2 Input: num = "030", Output: false

E.g 3 Input: num = "8", Output: false

```cpp
bool digitCount(string num) {
    string _tmp = num;
    std::sort(_tmp.begin(), _tmp.end());
    
    int sz = 0;

    if (_tmp[_tmp.size() - 1] - 48 >= _tmp.size()){
        sz = _tmp[_tmp.size() - 1] - 48 + 1;
    } else sz = _tmp.size();

    int hash_table[sz];

    for (int i = 0; i < sz; i++){
        hash_table[i] = 0;
    }

    for (int i = 0; i < num.size(); i++){
        hash_table[num[i] - 48] += 1; 
    }

    for (int i = 0; i < num.size(); i++){
        if (num[i] - 48 != hash_table[i]) return false;
    }
    return true;
}
```
# Count total duplicate characters inside a string
```c
char str[] = "HelloWorld";
int hash_table[58];// 26 lowercase + 26 uppercase + symbols between "A" to "a"

for (int i = 0; i < 58; i++){
    hash_table[i] = 0; 
}

for (int i = 0; i < sizeof(str); i++){
    hash_table[str[i] - 65] += 1; 
}

for (int i = 0; i < sizeof(str); i++){
    printf("%d ", hash_table[str[i] - 65]);
}
```
