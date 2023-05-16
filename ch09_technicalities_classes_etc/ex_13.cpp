/*
13. Design and implement a rational number class, Rational.
    A rational number has two parts: a numerator and a denominator,
    for example, 5/6 (five-sixths, also known as approximately .83333).
    Look up the definition if you need to.
    
    Provide assignment, addition, subtraction, multiplication, division, and equality operators.
    Also, provide a conversion to double. Why would people want to use a Rational class?

        My answer:
            Rational class has infinite precision, unlike a double,
            assuming we don't run out of space for the numerator/denominator.
*/
#include <iostream>
#include <numeric>
using namespace std;

class Rational {
    public:
        Rational(int n, int d);
        Rational(int c);
        int numerator() const { return _numerator; }
        int denominator() const { return _denominator; }
        double to_double() const { return double(_numerator) / _denominator; }
    private:
        int _numerator;
        int _denominator;
};
Rational::Rational(int n, int d) {
    _numerator = ((n > 0) == (d > 0)) ? abs(n) : abs(n)*-1;
    _denominator = abs(d);
}
Rational::Rational(int c) : _numerator {c}, _denominator {1} {}

Rational reduce(int n, int d) {
    int greatest_common_denominator = std::gcd(d, n);
    if (greatest_common_denominator > 1) {
        d /= greatest_common_denominator;
        n /= greatest_common_denominator;
    }
    return Rational(n, d);
}


// Addition is commutative!
Rational operator+(const Rational& r1, const Rational& r2) {
    int new_denominator = std::lcm(r1.denominator(), r2.denominator());
    int factor1 = new_denominator / r1.denominator();
    int factor2 = new_denominator / r2.denominator();
    int new_numerator = r1.numerator()*factor1 + r2.numerator()*factor2;
    return reduce(new_numerator, new_denominator);
}
Rational operator+(const Rational& r, const int c) { return r + Rational(c); }
Rational operator+(const int c, const Rational& r) { return r + c; }


// Multiplication is commutative!
Rational operator*(const Rational& r1, const Rational& r2) {
    return reduce(r1.numerator()*r2.numerator(), r1.denominator()*r2.denominator());
}
Rational operator*(const Rational& r, const int c) {
    return reduce(r.numerator()*c, r.denominator());
}
Rational operator*(const int c, const Rational& r) { return r*c; }


// Subtraction can be defined in terms of addition/multiplication.  It is NOT commutative.
Rational operator-(const Rational& r1, const Rational& r2) { return r1 + -1*r2; }
Rational operator-(const Rational& r, const int c) { return r + -1*c; }
Rational operator-(const int c, const Rational& r) { return c + -1*r; }


// Division is NOT commutative, but it can be defined in terms of multiplication!
Rational operator/(const Rational& r1, const Rational& r2) {
    return r1 * Rational(r2.denominator(), r2.numerator());
}
Rational operator/(const Rational& r, const int c) {
    int num = (c > 0) ? r.numerator() : r.numerator()*-1;
    return Rational(num, r.denominator() * c);
}
Rational operator/(const int c, const Rational& r) {
    return c * Rational(r.denominator(), r.numerator());
}

bool operator==(const Rational& r1, const Rational& r2) {
    return ((r1.numerator() == r2.numerator()) && (r1.denominator() == r2.denominator()));
}

ostream& operator<<(ostream& os, const Rational& r) { return os << r.numerator() << "/" << r.denominator(); }

int main() {

    Rational r1 {2, 3};
    Rational r2 {1, 4};
    cout << "r1: " << r1 << "\n"
         << "r2: " << r2 << "\n"
         << "r1 + r2: " << r1 + r2 << "\n"
         << "r1 +  1: " << r1 + 1 << "\n"
         << "r1 -  1: " << r1 - 1 << "\n"
         << "r1 - r2: " << r1 - r2 << "\n"
         << "r2 - r1: " << r2 - r1 << "\n"
         << "r1 * r2: " << r1 * r2 << "\n\n";

    Rational r3 {-1, 5};
    Rational r4 {1, -5};
    Rational r5 {-1, -5};
    cout << "r3: " << r3 << "\n"
         << "r4: " << r4 << "\n"
         << "r5: " << r5 << "\n"
         << "r3 + r1: " << r3 + r1 << "\n"
         << "r3*5: " << 5*r3 << "\n"
         << "r3*5 + r1: " << r3*5 + r1 << "\n\n";
          
    cout << "r3 / r5: " << r3/r5 << "\n"
         << "r3 / -1: " << r3/-1 << "\n\n";

    cout << "Rational(1, 2).to_double(): " << Rational(1, 2).to_double() << "\n"
         << "Rational(1, 3).to_double(): " << Rational(1, 3).to_double() << "\n\n";

    return 0;
}


/*
NOTES

Design choice: all fractions stored as reduced.  Operations automatically reduce fractions.


Class design
------------

First take had getters/setters for numerator/denominator - 4 functions.

Second take removed these, as I felt they were clunky.  Should only need to set once, and from then on get, as
Rational is an immutable object.  Any time we want to operate on it we get a new one (no ++ / -- operator).

Third take added a third variable: "negative", to indicate when the fraction is negative overall.

Fourth take: removed "negative" variable.  Instead, will always store the negative sign in the numerator!



Question - is there a way to make arguments order-agnostic?
    Guess: no, since that would change the meaning of the operator overloading (for when (a + b) != (b + a))
Question - is there a way to "overload" the built-in `double()` function to take Rational
    and specify a custom rule for it?  (Is there even a way to do this in Python??)
*/
