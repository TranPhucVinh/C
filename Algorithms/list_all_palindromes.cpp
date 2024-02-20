#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUMBER 99999999

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
int generate_palindromes(int i, int is_odd){
    int tmp;
    if (is_odd){
        tmp = i/10;
    } else {
        tmp = i;
    }
        
    while(tmp > 0){
        i = i * 10 + (tmp % 10);
        tmp = tmp / 10;
    }
    return i;
}

int main() {
    // listPalindrome(MAX_NUMBER);// This will take a few seconds to run as having big time complexity

    vector<int> palindromes;

    // This will take less than 1 sec to complete 
    // This for loop will generate odd length palindromes first then go with even length palindromes
    for (int k = 0; k < 2; k++){
        int i = 1;
        
        while(generate_palindromes(i, k%2) < MAX_NUMBER){
            palindromes.push_back(generate_palindromes(i,k%2));
            i += 1;
        }
    }

    std::sort(palindromes.begin(), palindromes.end());

    for (int i = 0; i < palindromes.size(); i++){
        cout << palindromes[i] << " ";
    }
    cout << endl;
    
    return 0;
}
