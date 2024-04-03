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
