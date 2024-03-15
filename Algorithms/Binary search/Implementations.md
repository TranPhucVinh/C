# Find a string inside a sorted string array
```cpp
string search_string(string target, string *str_arr, int start_index, int end_index) {
    int middle = 0;
    if (start_index == end_index) {
        if (target == str_arr[start_index]){
            cout << target << " found at " << start_index << endl;
            return target;
        } else {
            cout << target << " not found\n";
            return "NULL";
        }
    }
    middle = (start_index + end_index)/2;// Middle index
    if (target == str_arr[middle]) {
        cout << target << " found at " << middle << endl;
        return target;
    }
    else if (target > str_arr[middle]){
        return search_string(target, str_arr, middle+1, end_index);
    } else {
        return search_string(target, str_arr, start_index, middle);
    }
    
    return 0;
}

int main(){
    string str[] = {"a", "ab", "abc", "abd", "b"};
    int str_arr_sz = sizeof(str)/sizeof(string);
    search_string("b", str, 0, str_arr_sz-1);
}
```
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