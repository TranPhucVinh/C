// remove algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::remove
#include <vector>     // std::cout
#include <string>     // std::cout

using namespace std;

// ASCII value
#define CHAR_0      48  // Character 0
#define CHAR_9      57  // Character 9
#define	UPPERCASE_A 65  
#define	UPPERCASE_Z 90 
#define	LOWERCASE_A 97
#define	LOWERCASE_Z 122
int main () {
    string s = "A man, a plan, a canal: Panama";
    string palindrome;

    for (int i = 0; i < s.size(); i++){
        if (((CHAR_0 <= s[i]) && (s[i] <= CHAR_9)) || ((UPPERCASE_A <= s[i]) && (s[i] <= UPPERCASE_Z)) || ((LOWERCASE_A <= s[i]) && (s[i] <= LOWERCASE_Z))){
            palindrome += tolower(s[i]);
        } 
    }
    std::cout << palindrome << "\n";

    int a = 0;
    for (int i=0; i < palindrome.size(); i++){
        if (palindrome[i]==palindrome[palindrome.size()-1-i]){a++;}
        else {
            cout << "String " << s << "is not palindrome\n";    
            exit(0);        
        }
    }
    if ((a==(palindrome.size()))){ 
        cout << "String " << s << " is palindrome\n";
    } 

    return 0;
}
