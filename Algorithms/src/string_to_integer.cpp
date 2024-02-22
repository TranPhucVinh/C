#include <iostream>     // std::cout
#include <algorithm>    // std::remove
#include <vector>     // std::cout
#include <string>     // std::cout
#include <cmath>

using namespace std;

// ASCII value
#define CHAR_0      48  // Character 0
#define CHAR_9      57  // Character 9
#define	UPPERCASE_A 65  
#define	UPPERCASE_Z 90 
#define	LOWERCASE_A 97
#define	LOWERCASE_Z 122
#define	PLUS        43  // +
#define	MINUS       45  // -
#define	DOT         46  // .

#define MAX_INT_SZ  10

class Solution {
public:
    int myAtoi(string s) {
        // Case "string s" is ""
        if (!s.size()) return 0;

        // Case "string s" is "+" or "-"
        if ((s.size() == 1) && ((s[0] == MINUS) || (s[0] == PLUS))) return 0;
        
        try {
            long long number = stoll(s);

            if (number < -pow(2, 31)) return -pow(2, 31);
            if (number > (pow(2, 31) - 1)) return (pow(2, 31) - 1);

            return number;

        } catch (...){
            // Case like "  +  413", " - 123": return 0;
            if (s.size() >= 3){
                for (int i = 0; i+2 < s.size(); i++){
                    if ((s[i] == ' ')&&((s[i+1] == PLUS)||(s[i+1] == MINUS))&&(s[i+2] == ' ')){
                        return 0;
                    }
                }
            }

            string parse_str;

            for (int i = 0; i < s.size(); i++){
                if (((CHAR_0 <= s[i]) && (s[i] <= CHAR_9)) 
                || ((UPPERCASE_A <= s[i]) && (s[i] <= UPPERCASE_Z)) 
                || ((LOWERCASE_A <= s[i]) && (s[i] <= LOWERCASE_Z)) 
                || (s[i] == PLUS) || (s[i] == MINUS)
                || (s[i] == DOT)
                ){
                    parse_str += tolower(s[i]); // Convert all chars to lower case for later steps to check only lower case
                } 
            }

            // Case "string s" is full of " " (empty space)
            if (!parse_str.size()) return 0;

            // Case ABC123; abc123,... return 0
            if ((LOWERCASE_A <= parse_str[0]) && (parse_str[0] <= LOWERCASE_Z)) return 0;

            // Case -A123; +A123 return 0
            if (((parse_str[0] == MINUS) && (LOWERCASE_A <= parse_str[1]) && (parse_str[1] <= LOWERCASE_Z))
                ||((parse_str[0] == PLUS) && (LOWERCASE_A <= parse_str[1]) && (parse_str[1] <= LOWERCASE_Z))
                ||(parse_str[0] == DOT)){
                    return 0;
            }

            // Case +-; -+; ++; -- e.g +-12; return 0
            if ((parse_str[0] == MINUS) && (parse_str[1] == PLUS)
                ||((parse_str[0] == PLUS) && (parse_str[1] == MINUS))
                ||((parse_str[0] == PLUS) && (parse_str[1] == PLUS))
                ||((parse_str[0] == MINUS) && (parse_str[1] == MINUS))){
                    return 0;
            }

            string str_to_long;// Convert string to long number
            for (int i = 0; i < parse_str.size(); i++){
                if (((CHAR_0 <= parse_str[i]) && (parse_str[i] <= CHAR_9))||(parse_str[i] == MINUS)||(parse_str[i] == PLUS)){
                    str_to_long += parse_str[i];
                }
            }
            // This for loop will also form str_to_long=12+34 but str_to_long is only used for checking, not converting
            
            cout << "debug: " << str_to_long << endl;// debug
            // Case "string s" is a very big string number, like 20000000000000000000, -9223372036854775809 
            if (str_to_long.size() > MAX_INT_SZ){
                if (str_to_long[0] != MINUS) return (pow(2, 31) - 1);
                else return -pow(2, 31);
            }
            else {
                long long number = stoll(parse_str);

                if (number < -pow(2, 31)) return -pow(2, 31);
                if (number > (pow(2, 31) - 1)) return (pow(2, 31) - 1);

                return number;
            }
        }
    }
};

int main(){
    Solution sl;
    cout << sl.myAtoi("3.14abc") << endl;
}
