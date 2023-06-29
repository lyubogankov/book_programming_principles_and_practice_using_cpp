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

https://stackoverflow.com/a/1691818 < seems like it's dependent on processor architecture + application binary interface (ABI)?
After reading more answers in the thread above, it sounded like the growth of the stack was related primarily to functions, and that variables could grow wherever.
I tried making two functions, f1() and f2(), but the results were inconclusive:

p1: 0x55990fff6e70
p2: 0x55990fff6e90  + 0x20
p3: 0x55990fff6eb0  + 0x20

i1: 0x7ffdb2a13424
i2: 0x7ffdb2a13428  + 0x04
i3: 0x7ffdb2a1342c  + 0x04

// printouts rearranged for address comparison
Within function f1, address of i:  0x7ffdb2a133fc
Within function f2, address of j:  0x7ffdb2a133fc  equal to f1 i?
Within function f1, address of p1: 0x55990fff6eb0
Within function f2, address of p2: 0x55990fff6eb0  equal to f1 p1?



*/

#include <iostream>
using namespace std;

void f1() {
    int i = 157315;
    cout << "Within function f1, address of i:  " << &i << '\n';
    int* p1 = new int;
    cout << "Within function f1, address of p1: " << p1 << '\n';
    delete p1;
}
void f2() {
    int j = 234568;
    cout << "Within function f2, address of j:  " << &j << '\n';
    int* p2 = new int;
    cout << "Within function f2, address of p2: " << p2 << '\n';
    delete p2;
}

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

    f1();
    f2();

    return 0;
}