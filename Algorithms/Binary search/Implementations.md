# Find a string inside a sorted string array
<details>
```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool found = false;// Mark if the target is found

int search_string(string target, vector<string> str_arr, int start_index, int end_index) {
    int middle = 0;
    if (start_index == end_index) {
        if (target == str_arr[start_index]) found = true;
        else found = false;
        return start_index;
    }
    middle = (start_index + end_index)/2;// Middle index
    if (target == str_arr[middle]) {
        found = true;
        return middle;
    }
    else if (target > str_arr[middle]){
        return search_string(target, str_arr, middle+1, end_index);
    } else {
        return search_string(target, str_arr, start_index, middle);
    }
    
    return 0;
}
#define TARGET "b"
int main(){
    vector<string> str = {"a", "ab", "abc", "abd", "b"};

    int ret = search_string(TARGET, str, 0, str.size());
    if (found) cout << TARGET << " found at " << ret << endl;
    else {
        // When ret is 0, TARGET is < lower bound of the array
        if (!ret) {
            cout << TARGET << " isn't found as it is less than the lower bound\n";  
            return 0;
        }
        if (ret == str.size()) cout << TARGET << " isn't found as it is bigger than the upper bound\n";
        else cout << TARGET << " isn't found while it inside range [lower bound, upper bound]\n";
    }
}
```
</details>

# Find all negative numbers inside an ascending array
```c
int find_last_occurrence(int *array, int start_index, int end_index) {
    int arr_sz = end_index+1;
    int middle = 0;
    if (start_index == end_index) {
        if (array[0] >= 0) return -1;// As there is no negative number inside array
        else return start_index;
    }

    middle = (start_index + end_index)/2;// Middle index

    if (array[middle] < 0){
        if (middle + 1 < arr_sz && array[middle + 1] >= 0) return middle;
        return find_last_occurrence(array, middle+1, end_index);
    } else {        
        return find_last_occurrence(array, start_index, middle);
    }
}

int main() {
    int array[] = {-5, -3, -1, -1, -1, 2, 4, 6, 8};
    int n = sizeof(array) / sizeof(int);

    int index = find_last_occurrence(array, 0, n);
    printf("Total negative number: %d\n", index + 1);

    return 0;
}
```
# Find all negative numbers inside a descending array
[binary_search_find_neg_num_descending_array.c](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/binary_search_find_neg_num_descending_array.c)

# Check if an index and its double existed inside an array

Ccheck if there exist two indices i and j in an array such that:

arr[i] == 2 * arr[j]

* [10, 2, 5, 3]: True [5, 10]
* {-10, 12, -20, -8, 15}: True [-10, -20]
* {3, 1, 7, 11}: False
* {-485, -242}: False

[binary_search_check_if_an_index_and_its_double_existed.c](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/binary_search_check_if_an_index_and_its_double_existed.c)
