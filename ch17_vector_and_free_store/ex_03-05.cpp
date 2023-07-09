/*
3. Write a function, void to_lower(char* s), 
    that replaces all uppercase characters in the C-style string s with their lowercase equivalents. 
    For example, `Hello, World!` becomes `hello, world!`.
    Do not use any standard library functions. 
    A C-style string is a zero-terminated array of characters, so if you find a char with the value 0 you are at the end.

4. Write a function, char* strdup(const char*), 
    that copies a C-style string into memory it allocates on the free store. 
    Do not use any standard library functions.

5. Write a function, char* findx(const char* s, const char* x), 
    that finds the first occurrence of the C-style string x in s.
*/

#include <iostream>
using namespace std;

// ex 03
void to_lower(char* s) {
    for (int i=0; s[i] != 0; i++)
        if (65 <= s[i] && s[i] <= 90)
            s[i] += 32;  // ascii: A = 65, a = 97
}

// ex 04
char* strdup(const char* s) {
    int size = 0;
    for (size=0; s[size] != 0; size++); // determine char array size
    
    char* ret = new char[size];
    for (int i=0; i<=size; i++)
        ret[i] = s[i];

    return ret;
}

// ex 05
char* findx_original(/*const*/ char* s, const char*x, bool printout=true) {
    
    // // Before I read the problem carefully:
    // this will return the (zero-indexed) index within `s` 
    //      of the first character in `x` if a match is found, otherwise `-1`.
    // ex: s = "Hello world", x = "world"
    //                ^ ret = 6

    // After seeing the return value, I guess I need to return a pointer 
    // to the start of the substring if it is found, otherwise `nullptr`?

    // Ok -- I tried this, and got a clangtidy error about converting from const char* -> char *...

    char* ret = nullptr;
    int j=0;
    for(int i=0; s[i] != 0; i++) {
        if (printout)
            cout << "    s[i]: " << s[i] << "    x[j]: " << x[j] << '\n';
        if (s[i] == x[j])
            j++;
        else if (x[j] == 0)
            ret = &(s[i-j]);
        else
            j = 0;
    }
    return ret;
}

// oh -- the issue was that `s`' and the return type need to /match/.  Both can be `const`!
const char* findx(const char* s, const char* x) {

    // from bewuethr's solution
    // https://github.com/bewuethr/stroustrup-ppp/blob/main/chapter17/chapter17_ex05.cpp
    if (x == 0)
        return s;

    int j=0;
    for (int i=0; s[i] != 0; i++) {
        // if we're (continuing) to match between s/x, advance j!
        if (s[i] == x[j])
            j++;
        // if we've hit the end of x, this means we have a match.
        else if (x[j] == 0)
            return &s[i-j];
        // otherwise, reset j -- no longer matching.
        else
            j = 0;
    }
    // if we haven't already returned, there is no match.
    return nullptr;
}

int main() {

    // ex 03
    // not sure whether I need to add the null terminator myself.
    // it seems that the null terminator is automatically added
    char s[] = "Hello, World!";
    cout << "before: " << s << "\n";
    to_lower(s);
    cout << "after:  " << s << "\n";

    // ex 04
    char* copied = strdup(s);
    cout << "original: " << s << '\n'
         << "copy:     " << copied << '\n';
    delete[] copied;

    // ex 05
    const char* substr1 = findx(s, "world");
    cout << "'world' within '" << s << "'? " << (substr1 != nullptr) << '\n';
    const char* substr2 = findx(s, "meme");
    cout << "'meme'  within '" << s << "'? " << (substr2 != nullptr) << '\n';

    return 0;
}