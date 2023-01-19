/*
Add to the program (from ex02) so that it can also convert from Kelvin -> Celsius.
*/

#include <iostream>
using namespace std;

double ctok(double c) {
    if (c < -273.15)
        throw runtime_error("Physically impossible temperature.");
    double k = c + 273.15;    
    return k;
}

// new code for exercise 05
double ktoc(double k) {
    if (k < 0)
        throw runtime_error("Physically impossible temperature");
    return k - 273.15;
}

int main() {
    double c = 0;
    cin >> c;
    double k = ctok( c );
    cout << "Converted to Kelvin: " << k << '\n';
    cout << "Converted back to C: " << ktoc(k) << '\n';
    return 0;
}