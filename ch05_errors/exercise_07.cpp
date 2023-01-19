/*
Write a program that computes the real roots of a quadratic equation given a, b, c.
When the program detects an equation with no real roots, have it print out a message.

How do you know that your results are plausible?  Can you check that they are correct?

> Two methods come to mind.
    1) mathematically, the roots of the equation can each be plugged into the equation
       and it should equate to 0.  Can use this property to write a test.

    2) Other programs exist to compute the roots of a quadratic - could compare against
       their output (using them as an "oracle").
*/

#include <iostream>
#include <cmath>
using namespace std;

void print_quadratic_roots(double a, double b, double c) {
    double to_be_square_rooted = b*b - 4*a*c;
    if (to_be_square_rooted < 0) {
        cout << "Unfortunately, the quadratic equation " << a << "x^2 + " << b << "x + " << c << " has no real roots.\n";
        return;
    }
    double x1 = (-1*b + sqrt(to_be_square_rooted)) /  2*a;
    double x2 = (-1*b - sqrt(to_be_square_rooted)) /  2*a;
    cout << "Roots: " << x1 << " (+), " << x2 << " (-)\n\n";
    cout << "Verifying (+) root: " << a*x1*x1 + b*x1 + c << " ?= 0\n";
    cout << "Verifying (-) root: " << a*x2*x2 + b*x2 + c << " ?= 0\n";
}

int main() {

    double a, b, c;

    cout << "=== (real) QUADRATIC ROOT FINDER === " << '\n'
         << "  Please ensure that your quadratic equation is of the form ax^2 + bx + c = 0" << '\n'
         << "  Please input constants a, b, and c separated by spaces: ";
    cin >> a >> b >> c;

    print_quadratic_roots(a, b, c);

    return 0;
}