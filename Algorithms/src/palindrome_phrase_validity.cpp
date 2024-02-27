#define CHAR_0      48  // Character 0
#define CHAR_9      57  // Character 9
#define	UPPERCASE_A 65  
#define	UPPERCASE_Z 90 
#define	LOWERCASE_A 97
#define	LOWERCASE_Z 122

bool isPalindrome(string s) {
    string palindrome;

    for (int i = 0; i < s.size(); i++){
        if (((CHAR_0 <= s[i]) && (s[i] <= CHAR_9)) || ((UPPERCASE_A <= s[i]) && (s[i] <= UPPERCASE_Z)) || ((LOWERCASE_A <= s[i]) && (s[i] <= LOWERCASE_Z))){
            palindrome += tolower(s[i]);
        } 
    }
    std::cout << palindrome << "\n";

    int a = 0;

    if (palindrome.size() == 3) {
        if (palindrome[0] == palindrome[2]) {
            return true;
        }
        else {
            return false;
        }
    }

    for (int i=0; i < palindrome.size()/2; i++){
        if (palindrome[i] == palindrome[palindrome.size()-1-i]) a++;
        else {   
            return false;
        }
    }
    if (a == palindrome.size()){ 
        return true;
    }
    return true;
}
