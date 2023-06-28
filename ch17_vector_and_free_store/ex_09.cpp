/*
9. Which way does the stack grow: up (toward higher addresses) or down (toward lower addresses)?
   Which way does the free store initially grow (that is, before you use delete)? Write a program to determine the answers.

Printout:

p1: 0x556db7894e70
p2: 0x556db7894e90  + 0x20
p3: 0x556db7894eb0  + 0x20

i1: 0x7ffeb28e7254
i2: 0x7ffeb28e7258  + 0x04
i3: 0x7ffeb28e725c  + 0x04

Based on the printout, both seem to grow upwards?

https://stackoverflow.com/a/1691818 < seems like it's process-architecture-dependent?
*/

#include <iostream>
using namespace std;

int main() {

    // heap growth:
    int* p1 = new int;
    int* p2 = new int;
    int* p3 = new int;

    cout << "p1: " << p1 << '\n'
         << "p2: " << p2 << '\n'
         << "p3: " << p3 << '\n';

    delete p1;
    delete p2;
    delete p3;

    // stack growth:
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    cout << "i1: " << &i1 << '\n'
         << "i2: " << &i2 << '\n'
         << "i3: " << &i3 << '\n';

    return 0;
}