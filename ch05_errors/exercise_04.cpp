/*
Place a check in ctok() that will produce an error if a temperature 
below -273.15'C is given (same program from ex02).
*/

#include <iostream>
using namespace std;

// Note - using the corrected code from exercise 02.

double ctok(double c) {
    if (c < -273.15)
        throw runtime_error("Physically impossible temperature.");
    double k = c + 273.15;    
    return k;
}

int main() {
    double c = 0;
    cin >> c;
    double k = ctok( c );
    cout << k << '\n';
    return 0;
}