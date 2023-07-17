/*
1. Define a global int array ga of ten ints initialized to 1, 2, 4, 8, 16, etc.

2. Define a function f() taking an int array argument and an int argument indicating the number of elements in the array.

3. In f():
    a. Define a local int array la of ten ints.
    b. Copy the values from ga into la.
    c. Print out the elements of la.
    d. Define a pointer p to int and initialize it with an array allocated on the free store with the same number of elements as the argument array.
    e. Copy the values from the argument array into the free-store array.
    f. Print out the elements of the free-store array.
    g. Deallocate the free-store array.

4. In main():
    a. Call f() with ga as its argument.
    b. Define an array aa with ten elements, and initialize it with the first ten factorial values (1, 2*1, 3*2*1, 4*3*2*1, etc.).
    c. Call f() with aa as its argument.
*/

#include <iostream>
using std::cout;

// 1.
int ga[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

// 2.
void f(int* arr, int size) {
    // 3a.
    int la[10];
    // 3b.
    for(int i=0; i<10; i++)
        la[i] = ga[i];
    // 3c.
    for(int i=0; i<10; i++)
        cout << "ga[" << i << "] = " << ga[i] << "\nla[" << i << "] = " << la[i] << "\n\n";
    
    // 3d.
    int* p = new int[size];
    // 3e. -- no bounds checking, we have to trust that user' provided array has the size they say it does!
    for(int i=0; i<size; i++)
        p[i] = arr[i];
    // 3f.
    for(int i=0; i<size; i++)
        cout << "p[" << i << "] = " << p[i] << '\n';
    // 3g.
    delete[] p;
}

int main() {

    // 4a.
    cout << "-------------------- f(ga, 10)\n";
    f(ga, 10);
    // 4b, 4c
    int aasize = 10;
    int aa[aasize];
    for (int i=0; i<aasize; i++) {
        aa[i] = 1;
        for(int j=1; j<=(i+1); j++)
            aa[i] *= j;
    }
    cout << "-------------------- f(aa, aasize)\n";
    f(aa, aasize);

    return 0;
}