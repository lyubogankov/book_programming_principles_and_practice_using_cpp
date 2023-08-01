/*
1. Define template<typename T> struct S { T val; };.
2. Add a constructor, so that you can initialize with a T.
3. Define variables of types S<int>, S<char>, S<double>, S<string>, and S<vector<int>>; 
    initialize them with values of your choice.
4. Read those values and print them.
5. Add a function template get() that returns a reference to val.
6. Put the definition of get() outside the class.
7. Make val private.
8. Do 4 again using get().
9. Add a set() function template so that you can change val.
10. Replace set() with an S<T>::operator=(const T&). Hint: Much simpler than §19.2.5.
11. Provide const and non-const versions of get().

12. Define a function template<typename T> read_val(T& v) that reads from cin into v.

13. Use read_val() to read into each of the variables from 3 except the S<vector<int>> variable.

14. Bonus: Define input and output operators (>> and <<) for vector<T>s.
    For both input and output use a { val, val, val } format. 
    That will allow read_val() to also handle the S<vector<int>> variable.

Remember to test after each step.
*/

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

// 1. struct definition
template<typename T>
struct S { 
    // T val; // public by default

    // 2. constructor
    S(T t) : val {t} {}

    // 5, 6, 11
    T& get();
    const T& get_const();
    void set(T t);

    // 10.
    S<T>& operator=(const T&);

// 7.
private:
    T val;
};

template<typename T> T& S<T>::get() { return val; }
template<typename T> const T& S<T>::get_const() { return val; }
template<typename T> void S<T>::set(T t) { val = t; }
template<typename T> S<T>& S<T>::operator=(const T& other) {
    if (this == &other)
        return *this;
    val = other.val;
    return *this;
}

void parts_three_and_four() {
    // 3.
    S<int> si {1};
    S<char> sc {'L'};
    S<double> sd {3.14159};
    S<string> ss {"string"};
    S<vector<int>> svi {{1, 2, 3}};

    // 4. -- first time (S.val public)
    /*
    cout << "4 (directly accessing val)\n";
    cout << "S<int>         si  contains: " << si.val  << '\n'
         << "S<char>        sc  contains: " << sc.val  << '\n'
         << "S<double>      sd  contains: " << sd.val  << '\n'
         << "S<string>      ss  contains: " << ss.val  << '\n'
         << "S<vector<int>> svi contains: { ";
    for(auto i : svi.val)
        cout << i << " ";
    cout << "}\n";
    */
    // 8. (4. -- second time, with S.val private)
    cout << "8 (using .get())\n";
    cout << "S<int>         si  contains: " << si.get() << '\n'
         << "S<char>        sc  contains: " << sc.get() << '\n'
         << "S<double>      sd  contains: " << sd.get() << '\n'
         << "S<string>      ss  contains: " << ss.get() << '\n'
         << "S<vector<int>> svi contains: { ";
    for(auto i : svi.get())
        cout << i << " ";
    cout << "}\n";
}
void test_set() {
    S<int> si {1};
    cout << "------------\n"
         << "Testing set:\n"
         << "    Original value:   " << si.get() << '\n';
    si.set(2);
    cout << "    Updated (1 -> 2): " << si.get() << '\n';
}
void test_equality() {
    S<int> si1 {1};
    S<int> si2 {2};
    cout << "-----------------\n"
         << "Testing equality:\n"
         << "    Before `si1=si2`:    si1: " << si1.get() << "   si2: " << si2.get() << '\n';
    si1 = si2;
    cout << "    After  `si1=si2`:    si1: " << si1.get() << "   si2: " << si2.get() << '\n';
}
void test_gets() {
    cout << "testing get versions\n"
         << "--------------------\n";
    // non-const version: we can capture the reference and manipulate it.
    S<int> si {1};
    cout << "si: " << si.get() << '\n';
    int& i = si.get();
    i = 2;
    cout << "si: " << si.get() << "  <- notice the change!\n";

    // const version
    // int& j = si.get_const(); // can't do this with the const version, get compiler error
    cout << "si, using const: " << si.get_const() << '\n';
}

int main() {
    parts_three_and_four();
    test_set();
    test_equality();
    test_gets();
    return 0;
}