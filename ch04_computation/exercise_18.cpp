/*
Write a program to solve quadratic equations of the form ax^2 + bx + c = 0.
Use doubles for user inputs a, b, and c.  Output both solutions to the equation.
*/
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;

int main() {

    // prompt user for a, b, c
    double a=0.0, b=0.0, c=0.0;

    cout << "QUADRATIC EQUATION SOLVER:\n"
         << "This program will solve a quadratic equation of the form ax^2 + bx + c = 0\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;

    // NOT USING COMPLEX NUMBERS
    // compute x1 and x2
    // x = (-b +/- sqrt(b^2 - 4ac)) / 2a
    // x1 = +, x2 = -
    /*
    double sqrt_arg = pow(b, 2) - 4*a*c;
    if (sqrt_arg < 0) {
        cout << "Sorry, cannot compute the solution -- negative squareroot.\n\n";
        return 0;
    }
    double x1 = (-1*b + sqrt(sqrt_arg)) / (2*a);
    double x2 = (-1*b - sqrt(sqrt_arg)) / (2*a);
    cout << "Solutions: x1 = " << x1 << ", x2 = " << x2 << "\n\n";
    */

    // USING COMPLEX NUMBERS
    // https://stackoverflow.com/a/32597522
    complex<double> ca (a, 0.0);
    complex<double> cb (b, 0.0);
    complex<double> cc (c, 0.0);
    complex<double> sqrt_arg = pow(b, 2) - 4*a*c;
    complex<double> x1 = (-1*b + sqrt(sqrt_arg)) / (2*a);
    complex<double> x2 = (-1*b - sqrt(sqrt_arg)) / (2*a);
    cout << "Solutions: x1 = " << x1 << ", x2 = " << x2 << "\n\n";

    return 0;
}
