/*
1. Write a template function f() that adds the elements of one vector<T> to the elements of another; 
    for example, f(v1,v2) should do v1[i]+=v2[i] for each element of v1.

2. Write a template function that takes a vector<T> vt and a vector<U> vu as arguments and returns the sum of all vt[i]*vu[i]s.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::min;
using std::ostream;
using std::vector;

template<typename T> void f(vector<T>& v1, const vector<T>& v2)
// Element-wise addition between two vectors, result stored into v1.
{
    int result_size = min(v1.size(), v2.size());
    for(int i=0; i<result_size; ++i)
        v1[i] += v2[i];
}

// from drill
template<typename T> ostream& operator<<(ostream& os, const vector<T>& vt) {
    cout << "{ ";
    for (T t : vt)
        cout << t << ' ';
    cout << "}";
    return os;
}
void test_f() {
    vector<int> v1 { 1, 2, 3 };
    vector<int> v2 { 4, 5, 6 };
    vector<int> v3 { 7, 8 };
    vector<int> v4 { 9, 10, 11, 12 };

    cout << "Original v1: " << v1 << '\n';
    // v1.size() == v2.size()
    f(v1, v2);
    cout << "f(v1, v2):   " << v1 << '\n';
    // v1.size() >  v2.size()
    f(v1, v3);
    cout << "f(v1, v3):   " << v1 << '\n';
    // v1.size() <  v2.size()
    f(v1, v4);
    cout << "f(v1, v4):   " << v1 << '\n';
}


int main() {
    test_f();

    return 0;
}