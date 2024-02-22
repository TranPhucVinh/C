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
