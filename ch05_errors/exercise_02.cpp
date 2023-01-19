/*
The following program takes in a temperature value in Celsius and converts it to Kelvin.
This code has many errors in it.  Find the errors, list them, and correct the code.

Error code all commented out, corrected lines placed after originals.
*/

#include <iostream>
using namespace std;

double ctok(double c) {

    // if we set it to int, we'll be truncating
    // vvv                 
    // int k = c + 273.15;
    double k = c + 273.15;

 //        vvvv  returning "int", also no semicolon
 // return int
    return k;

}

int main() {

    double c = 0;

    //     v  we never defined variable called d 
//  cin >> d;
    cin >> c;

//                  vvv   don't pass in the string, pass the value we requested from user
//  double k = ctok("c");
    double k = ctok( c );

//  capitalized, should be lowercase
//  v             v  wrong slash
//  Cout << k << '/n';
    cout << k << '\n';

    // wasn't sure whether not returning a value would be an error, but no issue?
    return 0;  // adding just in case.
}