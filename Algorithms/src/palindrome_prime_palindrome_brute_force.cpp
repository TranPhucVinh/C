#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int primePalindrome(int n) {
        if ((n == 1) || (n==2)) return 2;
        if (10000000 <= n && n < 1000000000) n = 100000000;
        while(true){
            if(check_palindrome(n)){
                if (check_prime(n)) break;
                else n += 1;
            } else n += 1;
        }
        return n;
    }
private:
    bool check_prime(int number){
        int total_divisor = 0;
        for (int i = 2; i <= sqrt(number); i++)
        {
            if ((number % i) == 0) total_divisor++;
        }
        if (total_divisor == 0) return true;
        else return false;
    }

    bool check_palindrome(int number) {
        int tmp = 0;
        int old_number = number;
        int new_number = 0;
        while(number != 0)
        {
            tmp = number%10;
            number = number/10;
            new_number = new_number*10 + tmp;
        }
        if (old_number == new_number) return true;
        else return false;
    }
};

int main() {
    Solution sl;
    cout << sl.primePalindrome(9989900) << endl;
    // sl.primePalindrome(8);
    return 0;
}
