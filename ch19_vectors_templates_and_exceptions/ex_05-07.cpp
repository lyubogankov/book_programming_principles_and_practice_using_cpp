/*
5. Define a class Int having a single member of class int. 
    Define constructors, assignment, and operators +, –, *, / for it. 
    Test it, and improve its design as needed (e.g., define operators << and >> for convenient I/O).

6. Repeat the previous exercise, but with a class Number<T> where T can be any numeric type. 
    Try adding % to Number and see what happens when you try to use % for Number<double> and Number<int>.

7. Try your solution to exercise 2 with some Numbers.
*/

#include <cmath>  // for fmod (#6)
#include <iostream>

// #7
#include <vector>
#include <memory>

// I tried including functionality from ex02, but it didn't work :(
// I was probably not using the compiler correctly?
// #include "ex_02.h"  // for #7

using namespace std;

// 5.
class Int {
private:
    int val;
public:
    Int()      : val {0} {}
    Int(int i) : val {i} {}
    int get() const { return val; }
    void set(int newval) { val = newval; }
    Int& operator=(const Int& other);
};
Int& Int::operator=(const Int& other) {
    if (this == &other)
        return *this;
    this->set( other.get() );
    return *this;
}
Int operator+(const Int& i1, const Int& i2) { return Int(i1.get() + i2.get()); }
Int operator-(const Int& i1, const Int& i2) { return Int(i1.get() - i2.get()); }
Int operator*(const Int& i1, const Int& i2) { return Int(i1.get() * i2.get()); }
Int operator/(const Int& i1, const Int& i2) { return Int(i1.get() / i2.get()); } // not checking for /0
ostream& operator<<(ostream& os, const Int& i) { 
    os << i.get();
    return os;
}
istream& operator>>(istream& is, Int& i) {
    int newval;
    if(is >> newval)
        i.set(newval);
    else
        is.clear();
    return is;
}
void test_int() {
    // default construction
    cout << "Default construction:    " << Int() << '\n';
    // single-argument construction
    cout << "Single-arg construction: " << Int(5) << '\n';
    // assignment
    Int i1, i2 {5};
    cout << "Before assignment, i1: " << i1 << "    i2: " << i2 << '\n';
    i1 = i2;
    cout << "After assignment (i1 = i2): " << i1 << '\n';
    // addition
    cout << "i1 + i2: " << i1 + i2 << '\n';
    // subtraction
    cout << "i1 - i2: " << i1 - i2 << '\n';
    // multiplication
    cout << "i1 * i2: " << i1 * i2 << '\n';
    // division
    cout << "i1 / i2: " << i1 / i2 << '\n';
}

// 6.
// I want to try out concepts here!
/*
Link save:

concepts:
- https://stackoverflow.com/questions/14294267/class-template-for-numeric-types
- https://stackoverflow.com/questions/70301363/c-how-to-enforce-the-templated-type-to-implement-a-certain-operators
    - https://stackoverflow.com/questions/54200988/why-do-we-require-requires-requires

- https://en.cppreference.com/w/cpp/language/constraints
- https://en.cppreference.com/w/cpp/concepts
- https://en.cppreference.com/w/cpp/header/type_traits
    - https://en.cppreference.com/w/cpp/types/is_arithmetic

upgrading gcc:
- https://azrael.digipen.edu/~mmead/www/mg/update-compilers/index.html
- https://forums.linuxmint.com/viewtopic.php?t=275611&sid=6ab575ef3ad14b36b82d95dd52f229b9&start=20

current stuff installed on my system:
$ which gcc
/usr/bin/gcc

$ which g++
/usr/bin/g++

$ g[cc, ++] --version
gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/
template<typename T>
class Number {
private:
    T val;
public:
    Number() : val {T(0)} {} // default constructor - initialize with zero!
    Number(T t) : val {t} {} // constructor with arg
    T get() const { return val; }
    void set(T newval) { val = newval; }
    Number<T>& operator=(const Number<T>& other);
};

template<typename T> Number<T>& Number<T>::operator=(const Number<T>& other) {
    if (this == &other)
        return *this;
    this->set( other.get() );
    return *this;
}

// // This block of arithmetic operator overloads only works between Number<T> and Number<U>, not raw ints / doubles, etc.  That's a pain.
template<typename T, typename U> Number<T> operator+(const Number<T>& n1, const Number<U>& n2) { return Number<T>(n1.get() + n2.get()); }
template<typename T, typename U> Number<T> operator-(const Number<T>& n1, const Number<U>& n2) { return Number<T>(n1.get() - n2.get()); }
template<typename T, typename U> Number<T> operator*(const Number<T>& n1, const Number<U>& n2) { return Number<T>(n1.get() * n2.get()); }
template<typename T, typename U> Number<T> operator/(const Number<T>& n1, const Number<U>& n2) { return Number<T>(n1.get() / n2.get()); } // not checking for /0
template<typename T, typename U> Number<T> operator%(const Number<T>& n1, const Number<U>& n2) { return Number<T>(fmod(n1.get(), n2.get())); } // not checking for /0

// // This block of arithmetic operator overloads should account for Number<> and any other numeric type!
template<typename T, typename U> Number<T> operator+(const Number<T>& n1, const U& n2) { return Number<T>(n1.get() + n2); }
template<typename T, typename U>         T operator+(const T& n1, const Number<U>& n2) { return         T(n1 + n2.get()); }

template<typename T, typename U> Number<T> operator-(const Number<T>& n1, const U& n2) { return Number<T>(n1.get() - n2); }
template<typename T, typename U>         T operator-(const T& n1, const Number<U>& n2) { return         T(n1 - n2.get()); }

template<typename T, typename U> Number<T> operator*(const Number<T>& n1, const U& n2) { return Number<T>(n1.get() / n2); }
template<typename T, typename U>         T operator*(const T& n1, const Number<U>& n2) { return         T(n1 / n2.get()); }

template<typename T, typename U> Number<T> operator/(const Number<T>& n1, const U& n2) { return Number<T>(n1.get() / n2); }
template<typename T, typename U>         T operator/(const T& n1, const Number<U>& n2) { return         T(n1 / n2.get()); }

template<typename T, typename U> Number<T> operator%(const Number<T>& n1, const U& n2) { return Number<T>(fmod(n1.get(), n2)); }
template<typename T, typename U>         T operator%(const T& n1, const Number<U>& n2) { return         T(fmod(n1, n2.get())); }

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& n) {
    os << n.get();
    return os;
}
template<typename T>
istream& operator>>(istream& is, Number<T>& n) {
    T newval;
    if (is >> newval)
        n.set(newval);
    else
        is.clear();
    return is;
}

template<typename T, typename U>
void number_test_suite(Number<T> nt, Number<U> nu, T default_t) {
    cout << "----------------------------------------\n";
    cout << "nt = " << nt << "  nu = " << nu << "\n\n";
    // construction
    Number<T> a {};
    cout << "Default construction yields: " << a << '\n';
    Number<T> b {default_t};
    cout << "Number<T> b {" << default_t << "} yields:   " << b << "\n\n";
    // assignment
    a = nt;
    cout << "Assignment: new a=" << a << "\n\n";
    // arithmetic
    cout << "Number<T> + Number<U> = " << nt + nu << '\n';
    cout << "Number<T> - Number<U> = " << nt - nu << '\n';
    cout << "Number<T> * Number<U> = " << nt * nu << '\n';
    cout << "Number<T> / Number<U> = " << nt / nu << '\n';
    cout << "Number<T> % Number<U> = " << nt % nu << "\n\n";
}

void test_number() {
    // 1. T = int, U = int
    Number<int> x = 5;
    Number<int> y = 7;
    number_test_suite(x, y, 3);
    // int, double:
    Number<int> i = 5;
    Number<double> d = 10.2;
    // 2. T = int, U = double
    number_test_suite(i, d, 4);
    // 3. T = double, U = int
    number_test_suite(d, i, 10.0);
}

// 7.
template<typename T, typename U>
double dot_product(const vector<T>& vt, const vector<U>& vu)
// sum(vt[i] * vu[i])
// I would like to be able to ensure, via concept, that types T and U can be multiplied.
{
    if(vt.size() != vu.size())
        throw runtime_error("vt.size() != vu.size()");

    double dotprod;
    for(int i=0; i<vt.size(); ++i)
        dotprod = dotprod + (vt[i]*vu[i]); // haven't defined +=

    return dotprod;
}

void test_dotprod_w_numbers() {
    vector<Number<int>> vi {1, 2, 3};
    vector<Number<double>> vd {10.2, 0.0, -2.7};

    cout << "printing vi:\n";
    for (auto element : vi) cout << "    " << element << '\n';

    cout << "printing vd:\n";
    for (auto element : vd) cout << "    " << element << '\n';
    
    cout << "dot(vi, vd) = " << dot_product(vi, vd) << '\n';
    cout << "dot(vd, vi) = " << dot_product(vd, vi) << '\n';
}

int main() {
    // test_int(); // 5.
    // test_number(); // 6.
    test_dotprod_w_numbers(); // 7.
    return 0;
}