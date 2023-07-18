/*
*Using std lib vector.

1. Define a global vector<int> gv; initialize it with ten ints, 1, 2, 4, 8, 16, etc.

2. Define a function f() taking a vector<int> argument.

3. In f():
    a. Define a local vector<int> lv with the same number of elements as the argument vector.
    b. Copy the values from gv into lv.
    c. Print out the elements of lv.
    d. Define a local vector<int> lv2; initialize it to be a copy of the argument vector.
    e. Print out the elements of lv2.

4. In main():
    a. Call f() with gv as its argument.
    b. Define a vector<int> vv, and initialize it with the first ten factorial values (1, 2*1, 3*2*1, 4*3*2*1, etc.).
    c. Call f() with vv as its argument.
*/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

// 1.
vector<int> gv {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

// 2.
void f(vector<int> av) {
    // 3a.
    vector<int> lv(av.size());
    // 3b. -- assuming av.size() >= gv.size()
    for(int i=0; i<gv.size(); i++)
        lv[i] = gv[i];
    // 3c.
    for(int i=0; i<10; i++)
        cout << "gv[" << i << "] = " << gv[i] << "\nlv[" << i << "] = " << lv[i] << "\n\n";

    // 3d.
    vector<int> lv2 {av};
    // 3e.
    for (int x : lv2)
        cout << x << '\n';
}

int main() {
    // 4a.
    cout << "-------------------- f(gv)\n";
    f(gv);
    // 4b, 4c
    vector<int> vv(10, 1);
    for(int i=1; i<vv.size(); i++)
        for(int j=2; j<=(i+1); j++)
            vv[i] *= j;
    cout << "-------------------- f(vv)\n";
    f(vv);

    return 0;
}