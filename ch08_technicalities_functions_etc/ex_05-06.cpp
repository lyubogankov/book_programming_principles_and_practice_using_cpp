/*
5. Write two functions that reverse the order of elements in a vector<int>.
     For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1.
   The first reverse function should produce a new vector with the reversed sequence, leaving its original vector unchanged.
   The other reverse function should reverse the elements of its vector without using any other vectors (hint: swap).

6. Write versions of the functions from exercise 5, but with a vector<string>.
        Thankfully, didn't have to re-write everything!  Was able to make the functions work for vectors of any type using templates.
        Templates haven't been introduced in the book yet but I found them in the cplusplus.com docs.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <class T> vector<T> reverse(vector<T> v) {
    vector<T> reversed;
    for(int i=v.size()-1; i>=0; i--) reversed.push_back(v[i]);
    return reversed;
}
template <class T> void reverse_inplace(vector<T>& v) {
    for(int i=0; i<v.size()/2; i++)
        swap(v[i], v[v.size()-1-i]);
}
template <class T> void print_v(const vector<T>& v) {
    cout << "\t";
    for (T x : v)
        cout << x << " ";
    cout << "\n";
}

int main() {

    // ex 05 part 1
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    cout << "original: ";
    print_v(v);
    cout << "reversed: ";
    print_v(reverse(v));

    // ex 05 part 2
    cout << "         original: ";
    print_v(v);
    reverse_inplace(v);
    cout << "in-place reversed: ";
    print_v(v);

    
    // ex 06
    cout << "\n\n";

    vector<string> vs = {"a", "b", "c"};
    cout << "original: ";
    print_v(vs);
    cout << "reversed: ";
    print_v(reverse(vs));

    cout << "         original: ";
    print_v(vs);
    reverse_inplace(vs);
    cout << "in-place reversed: ";
    print_v(vs);
}