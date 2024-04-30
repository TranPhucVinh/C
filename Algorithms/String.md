# Time conversion in AM/PM format
* 12:01:00PM -> 12:01:00
* 12:01:00AM -> 00:01:00
* 07:05:45PM -> 19:05:45
* 12:45:54PM -> 12:45:54

<details>
  
```cpp
vector<string> splitStringByDelimiter(string s, string delim) {
    vector<string> all_substr;
    std::size_t index = s.find(delim, 0);
    string sub_str  = s.substr(0, index);
    string new_string = s.substr(index+1);

    while (index != string::npos) { 
        if (sub_str != delim && sub_str.size() >= 1) {
            all_substr.push_back(sub_str);
        }

        index = new_string.find(delim, 0);
        sub_str  = new_string.substr(0, index);
        new_string = new_string.substr(index+1);
    }

    if (sub_str != delim && sub_str.size() >= 1) {
        all_substr.push_back(sub_str);
    }

    return all_substr;
}

string timeConversion(string s) {
    string twenty_4hr_clock;

    vector<string> all_substr = splitStringByDelimiter(s, ":");
    std::string clock =  all_substr[2].substr(2, 2);
    int hour = stoi(all_substr[0]);
    if (clock == "AM") {
        if (hour == 12) return "00:" + all_substr[1] + ":" + all_substr[2].substr(0, 2);
        else return s.substr(0, 8);// Test case: 06:40:03AM -> 06:40:03
    }
    else {
        if (hour == 12 && all_substr[1].substr(0, 2) == "00" && all_substr[2].substr(0, 2) == "00")
        return "00:00:00AM";

        if (hour < 12) hour +=12;
    }
    twenty_4hr_clock = std::to_string(hour) + ":" + all_substr[1] + ":" + all_substr[2].substr(0, 2);
    return twenty_4hr_clock;
}
```
</details>

# [Convert a valid Roman numerals to integer, using map](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/src/map_roman_numerals_to_integer.cpp)
# [Convert an integer to Roman numeral by using vector tuple](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/src/vector_tuple_integer_to_roman_numeral.cpp)
# Convert string to integer
Create a function to convert a string to integer with the following conditions:

* Read in and ignore any leading whitespace.
* Check if the next character (if not already at the end of the string) is **-** or **+**. Read this character in if it is either. This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
* Read in next the characters until the next non-digit character or the end of the input is reached. The rest of the string is ignored.
* Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
* If the integer is out of the 32-bit signed integer range **[-2^31, 2^31 - 1]**, then clamp the integer so that it remains in the range. Specifically, integers less than **-2^31** should be clamped to **-231**, and integers greater than **2^31 - 1** should be clamped to **2^31 - 1**.

Some test cases:
* 42 -> 42
* "   -42" -> -42
* "4193 with words" -> 4193
* 3.14abc -> 3
* "  +0 123" -> 0
* "20000000000000000000" -> 2147483647
* "-9223372036854775809" -> -2147483648

Leetcode: [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/description/)

Source code: [string_to_integer.cpp](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/string_to_integer.cpp)

# Repeated substring pattern

Given a string **s**, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.

* s = "abab" -> true as it is the substring **ab** twice
* s = "aba" -> false
* s = "abcabcabcabc" -> true as it is the substring "abc" four times or the substring "abcabc" twice.

**Algorithm**: 
* The substring size must not be greater than half length of string **s**: ``substr_size <= length/2``
* String **s** length must be divided by the substring size: ``substr_size*k = length``
From that, we will generate all possible size of the substring then start finding if at least one among them can form the original string **s**.

Source code: [string_repeated_substring_pattern.cpp](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/string_repeated_substring_pattern.cpp)
