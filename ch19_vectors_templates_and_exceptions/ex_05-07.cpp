/*
5. Define a class Int having a single member of class int. 
    Define constructors, assignment, and operators +, –, *, / for it. 
    Test it, and improve its design as needed (e.g., define operators << and >> for convenient I/O).

6. Repeat the previous exercise, but with a class Number<T> where T can be any numeric type. 
    Try adding % to Number and see what happens when you try to use % for Number<double> and Number<int>.

7. Try your solution to exercise 2 with some Numbers.
*/

#include <iostream>
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
template<typename T> Number<T> operator+(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() + n2.get()); }
template<typename T> Number<T> operator-(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() - n2.get()); }
template<typename T> Number<T> operator*(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() * n2.get()); }
template<typename T> Number<T> operator/(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() / n2.get()); } // not checking for /0

// still need << and >> operators
void test_number() {

}

int main() {
    test_int();
    return 0;
}