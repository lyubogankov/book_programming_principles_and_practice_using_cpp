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

int main() {
    test_int();
    return 0;
}