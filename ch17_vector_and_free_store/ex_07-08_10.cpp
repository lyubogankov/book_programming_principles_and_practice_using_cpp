/*
7. Write a program that reads characters from cin into an array that you allocate on the free store. 
    Read individual characters until an exclamation mark (!) is entered. 
    Do not use a std::string. Do not worry about memory exhaustion.

8. Do exercise 7 again, but this time read into a std::string 
    rather than to memory you put on the free store (string knows how to use the free store for you).

    *Needed to clear cin's input buffer after each reading because we stop processing characters after the first
        exclamation point!  This works fine with just one input loop, but messes up when we have more than one.

10. Look at your solution of exercise 7. 
    Is there any way that input could get the array to overflow; 
    that is, is there any way you could enter more characters than you allocated space for (a serious error)? 
    Does anything reasonable happen if you try to enter more characters than you allocated?

    ---
    Huh -- I tried allocating a single character, and entered a lengthy input (100+ characters).
    The readback worked just fine, which means I overwrote unallocated space?

    I was expecting the program to crash, but it behaved normally for the time being.
    Not sure at what point writing beyond array bounds would crash the program, but it's not good practice.
*/

#include <limits>
#include <iostream>
#include <string>
using namespace std;

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

void ex_07(const int arraysize = 1000) {
    cout << "... allocating an array with " << arraysize << " elements.\n";
    char* userinput = new char[arraysize];

    char c;
    int idx = 0;

    cout << "\nPlease enter characters, terminate with '!':\n";
    while(cin >> noskipws >> c && c != '!') {
        // cout << "    " << int(c) << '\n';
        userinput[idx++] = c;
    }
    cin.ignore(max_size, '\n'); // "eat" all remaining input after first exclamation point.
    cout << "Here is what you entered:\n" << userinput << '\n';

    delete[] userinput;
}

void ex_08() {
    string userinput;
    char c;
    cout << "\nPlease enter characters, terminate with '!':\n";
    while(cin >> noskipws >> c && c != '!') {
        // cout << "    " << int(c) << '\n';
        userinput.push_back(c);
    }
    cin.ignore(max_size, '\n');
    cout << "Here is what you entered:\n" << userinput << '\n';
}

int main() {
    ex_07();
    ex_08();
    ex_07(1);
    return 0;
}