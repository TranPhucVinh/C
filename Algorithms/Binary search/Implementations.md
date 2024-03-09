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