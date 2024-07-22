# Happy number

A happy number is a number defined by the following process:

* Starting with any positive integer, replace the number by the sum of the squares of its digits.
* Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy.

```cpp
int total_square(int n){
	int square_sum = 0;
	while (n > 0){
		square_sum += pow(n%10, 2);
		n = n/10;
	}
	return square_sum;
}

vector<int> check_happy_vec;

bool isHappy(int n) {
	n = total_square(n);

	if (n == 1) return true;
	else {
		vector<int>::iterator element;

		element = find(check_happy_vec.begin(), check_happy_vec.end(), n);

		if (element != check_happy_vec.end()) return false;
		else {
			check_happy_vec.push_back(n);
			return isHappy(n);
		}
	}
    return false;
}
```
# Sum from 1 to n

Features: Number ``n`` entered as ``main()`` argument

Handle error:

* Must enter 1 parameter for n, less than 1 or more than 1 parameter is not accepted.
* Accept value of ``n`` is integer ``2147483647``
* Negative number is not accepted
* Invalid number ``123abc`` is not accepted (for the parsing operation of ``atoi()``)

For the max accepted number of ``2147483647``, the result must be ``unsigned long int``, not ``int``.

Program: [sum_from_1_to_n.c](../../src/sum_from_1_to_n.c)
