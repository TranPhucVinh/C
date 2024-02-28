bool isPalindrome(string s) {
        int a = 0;

        if (s.size() == 3) {
            if (s[0] == s[2]) return true;
            else return false;
        }

        for (int i=0; i < s.size()/2; i++){
            if (s[i]==s[s.size()-1-i]) a++;
            else return false;
        }

        if (a == s.size()/2) return true;
        return true;
}

bool validPalindrome(string s) {
    int a = 0;

    if (s.size() == 3) {
        if ((s[0] == s[2])||(s[0] == s[1])||(s[1] == s[2])) return true;
        else return false;
    }

    for (int i=0; i < s.size()/2; i++){
        if (s[i] == s[s.size()-1-i]) a++;
        else {
            string check_string = s;
            check_string.erase(i, 1);// Delete 1 character from index i
            if (isPalindrome(check_string)) return true;
            else {
                check_string = s;
                check_string.erase(s.size()-1-i, 1);// Delete 1 character from index s.size()-1-i
                if (isPalindrome(check_string)) return true;
                else return false;
            }
        }
    }
    if (a == s.size()/2) return true;
    return true;
}
