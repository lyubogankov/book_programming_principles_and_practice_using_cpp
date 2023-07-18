/*
1. Write a function, char* strdup(const char*), that copies a C-style string into memory it allocates on the free store. 
    Do not use any standard library functions. Do not use subscripting; use the dereference operator * instead.

2. Write a function, char* findx(const char* s, const char* x), that finds the first occurrence of the C-style string x in s. 
    Do not use any standard library functions. Do not use subscripting; use the dereference operator * instead.

3. Write a function, int strcmp(const char* s1, const char* s2), that compares C-style strings. 
    Let it return:
    - a negative number if s1 is lexicographically before s2
    - zero if s1 equals s2
    - a positive number if s1 is lexicographically after s2
    Do not use any standard library functions. Do not use subscripting; use the dereference operator * instead.

4. Consider what happens if you give strdup(), findx(), and strcmp() an argument that is not a C-style string. Try it! 
    
    First figure out how to get a char* that doesn’t point to a zero-terminated array of characters and then use it 
    (never do this in real — non-experimental — code; it can create havoc). 
    
    Try it with free-store-allocated and stack-allocated “fake C-style strings.” 
    If the results still look reasonable, turn off debug mode. 
    
    Redesign and re-implement those three functions so that they take another argument 
    giving the maximum number of elements allowed in argument strings. 
    Then, test that with correct C-style strings and “bad” strings.
*/

#include <iostream>
using std::cout;

int c_strlen(const char* s) 
// Returns the length of the C-style string, *including* '\0'
{
    int s_len = 0;
    while(*(s + sizeof(char)*s_len) != '\0')
        s_len++;
    return s_len + 1;
}

// 1.
char* strdup(const char* s) {
    int s_len = c_strlen(s);
    char* dup = new char[s_len];
    for(int i=0; i<s_len; i++)
        *(dup + sizeof(char)*i) = *(s + sizeof(char)*i);
    return dup;
}

int main() {
    char s[] {"meme"};
    char* dup = strdup(s);

    cout << "s:   " << s   << "   len: " << c_strlen(s)   << '\n'
         << "dup: " << dup << "   len: " << c_strlen(dup) << '\n';

    delete[] dup;
    return 0;
}