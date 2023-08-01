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
int book_c_strlen(const char* s) 
// does NOT include the null terminator
{
    int len = 0;
    while(*s) { ++len; ++s; }
    return len;
}

char* strdup(const char* s) 
// 1. copies a C-style string into memory it allocates on the free store
{
    int s_len = c_strlen(s);
    char* dup = new char[s_len];
    for(int i=0; i<s_len; i++)
        *(dup + sizeof(char)*i) = *(s + sizeof(char)*i);
    return dup;
}
 char* findx(const char* s, const char* x)
// 2. finds the first occurrence of the C-style string x in s
// TIL about `const_cast<T>`!  https://en.cppreference.com/w/cpp/language/const_cast
{
    int s_len = c_strlen(s);
    int x_len = c_strlen(x);
    // can't find substring if 'substring' is larger than search string!
    // also, if either the search or find strings only contain null terminator or are blank, also can't find substr.
    if (x_len > s_len || s_len <= 1 || x_len <= 1)
        return nullptr;
    
    int xi = 0;
    // iterate over all non-terminating characters in s
    for(int si=0; si<(s_len-1); si++) {
        // xi^th char in x matches si^th char in s!
        if (*(s + si*sizeof(char)) == *(x + xi*sizeof(char))) {
            // x_len is 1-indexed and inclusive of '\0', so we terminate when we're at the last non-terminating char
            if (xi == x_len - 2)
                return const_cast<char*>(s + (si-xi)*sizeof(char));
            xi++;
        }
    }
    return nullptr;
}

int strcmp(const char* s1, const char* s2)
// 3. lexographically compares C-style strings. Return vals: -1 means s1 < s2, 0 means s1 == s2, +1 means s1 > s2
{
    while(*s1 && *s2) {
        if(*s1 < *s2) return -1;
        if(*s1 > *s2) return  1;
        s1++;
        s2++;
    }
    // special case: if one of the strings, `x`, is a substring of the other (`y`) and starts and idx 0, 
    // the loop will terminate since all chars are equal until one of the strings is exhausted.
    // however, we can't say for certain yet that they're exactly the same string!
    if(*s1) return  1;  // s1 >  s2 (s1 still has characters left)
    if(*s2) return -1;  // s1  < s2 (s2 still has characters left)
    return 0;           // s1 == s2 (neither s1 nor s2 have chars left)
}

void print_arr(char* arr) {
    cout << "\"";
    while(*arr) { 
        cout << *arr;
        arr++;
    }
    cout << "\"";
}


int main() {

    // testing 1. (strdup)
    char og[] {"woah."};
    char* dup = strdup(og);
    cout << "og:  " << og  << "   len: " << c_strlen(og)  << "    vs book's: " << book_c_strlen(og)  << '\n'
         << "dup: " << dup << "   len: " << c_strlen(dup) << "    vs book's: " << book_c_strlen(dup) << "\n\n";
    delete[] dup;


    // testing 2. (findx)
    char empty_string[] {""};
    char is_substr[] {"mnop"};
    char isnt_substr[] {"zyxw"};
    char haystack[] {"abcdefghijklmnopqrstuvwxyz"};

    char* result = findx(empty_string, isnt_substr);
    cout << "case 1: `s` is an empty string                                      (testing `result == nullptr`):  " << (result==nullptr) << '\n';

    result = findx(haystack, empty_string);
    cout << "case 2: `x` is an empty string                                      (testing `result == nullptr`):  " << (result==nullptr) << '\n';

    result = findx(isnt_substr, haystack);
    cout << "case 3: `x` has more characters than `s`                            (testing `result == nullptr`):  " << (result==nullptr) << '\n';

    result = findx(haystack, isnt_substr);
    cout << "case 4: `x` has fewer char than `s` but is not contained within `s` (testing `result == nullptr`):  " << (result==nullptr) << '\n';

    result = findx(haystack, is_substr);
    cout << "case 5: `x` has fewer char than `s` and is     contained within `s`: " << '\n';
    cout << "\t `result == nullptr`          ?  " << (result==nullptr) << '\n'
         << "\t `result == (&haystack + 12)` ?  " << (result == (haystack + 12)) << "\n\n";


    // testing 3. (strcmp)
    char special_substr[] {"abcd"};
    cout << "case 1: `s1` empty:  " << strcmp(empty_string, haystack) << "\t\ts1: " << empty_string << "    s2: " << haystack << '\n'
         << "case 2: `s2` empty:  " << strcmp(haystack, empty_string) << "\t\ts1: " << haystack << "    s2: " << empty_string << '\n'
         << "case 3: `s1  < s2`:  " << strcmp(is_substr, isnt_substr) << "\t\ts1: " << is_substr << "    s2: " << isnt_substr << '\n'
         << "case 4: `s1 > s2` :  " << strcmp(isnt_substr, is_substr) << "\t\ts1: " << isnt_substr << "    s2: " << is_substr << '\n'
         << "case 5: `s1 == s2`:  " << strcmp(is_substr, is_substr)   << '\n'
         << "case 6: `s1` is substring of `s2`, starting at idx0:  " << strcmp(haystack, special_substr) << "\t\ts1: " << haystack << "    s2: " << special_substr << "\n\n";

    // 4 - non-C-string-char-arrays
    //      I get a clang warning, and compiler error.  If I run with `-fpermissive` error -> warning.
    char fakecstr_stack[4] {"woah"};
    //      Interesting - difference in behavior based on how I initialize the heap char array
    //          When I use the for loop (even when I exceed array bounds) the duplicate prints/works fine,
    //            and ending char is always 0 (as int).
    //
    //          However, when I use the curly-brace initializer syntax:
    //          with # chars >= len, `print_arr` prints both the original and duplicate string as "" (totally empty), 
    //            though heap len reports 2
    char *fakecstr_heap = new char[4] {"zzzzzzz"};
    // const int heap_overbound = 10;
    // for(int i=0; i<heap_overbound; i++)
    //     *(fakecstr_heap + sizeof(char)*i) = 'z';
    // cout << int(*(fakecstr_heap + sizeof(char)*heap_overbound)) << '\n';
    print_arr(fakecstr_heap);
    cout << " <- this is allegedly what's inside the heap char pointer\n";

    // // strdup causes the following error: "munmap_chunk(): invalid pointer  Aborted (core dumped)"
    // char* fakecstr_dup = strdup(fakecstr_stack);
    // cout << "duplicate contents (stack): ";
    // print_arr(fakecstr_dup);

    // delete[] fakecstr_dup;
    char* fakecstr_duph = strdup(fakecstr_heap);
    print_arr(fakecstr_duph);
    cout << "  <- duplicate contents (heap)\n";
    delete[] fakecstr_duph;

    // findx - before this, cstrlen
    //  stack: 9
    //  heap:  2
    cout << "len, stack: " << c_strlen(fakecstr_stack) << '\n';
    cout << "len, heap:  " << c_strlen(fakecstr_heap) << '\n';

    // 1: both nullptr (no match)
    // 2: both nullptr (no match)
    // 3: both nullptr (no match)
    // 4: stack matches, heap doesn't
    cout << "case 1: `x` is empty string:\n"
         << "    stack: " << (findx(fakecstr_stack, "") == nullptr) << "\n"
         << "     heap: " << (findx(fakecstr_heap,  "") == nullptr) << "\n"

         << "case 2: `x` larger than `s`:\n"
         << "    stack: " << (findx(fakecstr_stack, "woahwoahwoah"    ) == nullptr) << "\n"
         << "     heap: " << (findx(fakecstr_heap,  "zzzzzzzzzzzzzzzz") == nullptr) << "\n"

         << "case 3: `x` has fewer characters than, but is not within, `s`:\n"
         << "    stack: " << (findx(fakecstr_stack, "no dice") == nullptr) << "\n"
         << "     heap: " << (findx(fakecstr_heap,  "no dice") == nullptr)<< "\n"

         << "case 4: `x` has fewer characters than, and is within, `s`:\n"
         << "    stack: " << (findx(fakecstr_stack, "w") == nullptr) << "\n"
         << "     heap: " << (findx(fakecstr_heap,  "z") == nullptr) << "\n";

    delete[] fakecstr_heap;


    return 0;
}