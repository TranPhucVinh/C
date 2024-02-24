#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int primePalindrome(int n) {
        if ((n == 1) || (n == 2)) return 2;
        if ((n >= 8) && (n <= 11)) return 11;

        int sz_number = 0;

        int _sz_number = to_string(n).size();
        if (_sz_number%2) sz_number = _sz_number;
        else sz_number = _sz_number + 1;

        for (int i = sz_number; i < 1e5; i++) {
            string palindrome = to_string(i);
            string reverse_num = palindrome;
            reverse(reverse_num.begin(), reverse_num.end());

            /*
                Only take odd number 123 to form the palindrome of 12321:
                get the sub string from its 1th index, so reverse_num.substr(1)
            */
            palindrome += reverse_num.substr(1);
            if ((stoll(palindrome) >= n) && (is_prime(stoll(palindrome)))) return stoll(palindrome); 
        }
        return -1;
    }
private:
    bool is_prime(int number){
        int total_divisor = 0;
        for (int i = 2; i <= sqrt(number); i++)
        {
            if ((number % i) == 0) total_divisor++;
        }
        if (total_divisor == 0) return true;
        else return false;
    }
};

int main() {
    Solution sl;
    cout << sl.primePalindrome(9989900) << endl;
    
    return 0;
}
