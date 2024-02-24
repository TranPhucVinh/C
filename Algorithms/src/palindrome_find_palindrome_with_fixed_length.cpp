#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class FindPalindrome {
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        // for odd number palindrome
        if (intLength%2) _half_length = intLength/2 + 1;
        else _half_length = intLength/2; // for even number palindrome
        int min = pow(10, _half_length-1), max = pow(10, _half_length) - 1;
        for (int i = 0; i < queries.size(); i++) {
            if (queries[i] > (max - min + 1)) _Palindromes.push_back(-1);
            else {
                int kth_num_to_gen_palindrome = min + queries[i] - 1;
                string palindrome = to_string(kth_num_to_gen_palindrome);
                string reverse_num = palindrome;
                reverse(reverse_num.begin(), reverse_num.end());

                /*
                    For even number 12 to form the palindrome of 1221
                    get the sub string from its 0th index, so reverse_num.substr(0)
                    For odd number 123 to form the palindrome of 12321:
                    get the sub string from its 1th index, so reverse_num.substr(1)
                */
                palindrome += reverse_num.substr(intLength%2);
                _Palindromes.push_back(stoll(palindrome));
            }
        }
        for (long long i = 0; i < _Palindromes.size(); i++){
           cout << _Palindromes[i] << endl;
        }        
        return _Palindromes;
    }
private:
    vector<long long> _Palindromes;
    int _half_length;

};

int main() {
    FindPalindrome pl;
    vector<int> queries{2,4,6};
    pl.kthPalindrome(queries, 4);
    return 0;
}
