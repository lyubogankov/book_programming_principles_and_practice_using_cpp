/*
14. Can we declare a non-reference function argument const (e.g., void f(const int);)? 
    What might that mean? Why might we want to do that?
    Why don’t people do that often?
    
    Try it; write a couple of small programs to see what works.

    ---

    Seems to work fine with the cases tested below.

    This might be useful if pass-by-value only makes a *shallow* copy of a nested data structure and
    we want to make it read-only in a single function.

    It probably doesn't come up often in C++, based on how the question is worded.
*/

#include <iostream>

using namespace std;

void f(const int i) {
    cout << i << "\n";
}

int main() {

    f(10);

    const int x = 5;
    f(5);

    int y = 15;
    f(y);

    return 0;
}