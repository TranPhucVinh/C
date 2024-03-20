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
This is an inefficient implementation of hash map as ``hash_table[17]`` has many un-used index. [Unordered map](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/Unordered%20map.md#use-unordered-map-to-count-total-duplicate-numbers-inside-an-array) is the best approach for it.

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
