bool repeatedSubstringPattern(string str) {
    vector<string> str_arr;

    vector<int> substr_size;
    for (int i = 1; i <= str.size()/2; i++){
        if (!(str.size() % i)) substr_size.push_back(i);
    }

    for (int i = 0; i < substr_size.size(); i++){
        str_arr.push_back(str.substr(0, substr_size[i]));
    }

    for (int i = 0; i < str_arr.size(); i++){
        // cout << str_arr[i] << endl;

        int total_unique_str = str.size() / str_arr[i].size();

        std::size_t index = str.find(str_arr[i], 0);

        int found = 0;
        while (index != string::npos) { 
            found += 1;
            index = str.find(str_arr[i], index + str_arr[i].size());
        } 
        cout << str_arr[i] << " " << found << " " << total_unique_str << endl;
        if (found == total_unique_str) return true;
    }
    return false;
}
