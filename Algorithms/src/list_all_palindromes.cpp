#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUMBER 99999999

using namespace std;

int reverse_number(int old_number) {
    int tmp;
    long new_number = 0; // As there is "new_number*10 + tmp" in later step, so
                         // new_number must be long
    if (old_number < 0) {
        printf("Negative number can't be reversed\n");
        exit(0);
    }
    while (old_number != 0) {
        tmp = old_number % 10;
        old_number = old_number / 10;
        new_number = new_number * 10 + tmp;
    }

    return new_number;
}

/*
    List all panlindrome by looping through all number is 
    a brute force approach which results in big time-complexity
*/
void listPalindrome(int max_number) {
    int pn_sz = 0;

    for (int i = 1; i < max_number; i++) {
        if (i == reverse_number(i)) {
            pn_sz += 1;
        }
    }

    int* pn_arr = (int*)malloc(sizeof(int) * pn_sz);

    int pn_index = 0;
    for (int i = 0; i <= max_number; i++) {
        if (i == reverse_number(i)) {
            pn_arr[pn_index++] = i;
        }
    }

    for (int i = 0; i <= pn_sz; i++) {
        printf("%d ", pn_arr[i]);
    }
}

/*
    Generate palindromes include:
    * Odd length palindromic numbers: 101, 111, 121,...
    * Even length palindromic numbers: 1001, 3223, 123321,...
*/
void generate_palindromes_with_length(long length){
    vector<long long> palindromes;

    if (length == 1){
        for (long long i = 1; i < 10; i++){
            palindromes.push_back(i);
        }
        return;
    }
    
    // If length is odd
    if (length%2){
        long half_length = (length - 1)/2;
        for (long long i = 0; i < 10; i++){
            for (long long j = pow(10, (half_length-1)); j < pow(10, half_length); j++){
                string reverse_j = to_string(j);
                reverse(reverse_j.begin(), reverse_j.end());
                palindromes.push_back(stoll(to_string(j) + to_string(i) + reverse_j, 0, 10));
            }
        } 
    } 
    // If length is even
    else {
        long long half_length = length/2;
        for (long long i = pow(10, (half_length-1)); i < pow(10, half_length); i++){
            string reverse_i = to_string(i);
            reverse(reverse_i.begin(), reverse_i.end());
            palindromes.push_back(stoll(to_string(i) + reverse_i, 0, 10));
        } 
    }

    std::sort(palindromes.begin(), palindromes.end());

    for (long long i = 0; i < palindromes.size(); i++){
       cout << palindromes[i] << endl;
    }
}

int main() {
    listPalindrome(MAX_NUMBER);// This will take a few seconds to run as having big time complexity

    generate_palindromes_with_length(15);
    
    return 0;
}
