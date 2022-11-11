/*
Exponential grains of rice on chessboard - doubles per square, starting with a single grain on first square.

Try to calculate the number of grains the inventor asked for, total (64 squares on chess board.)
You'll find the number is so large it won't fit into an int, or a double.

Observe what happens when the number gets too large to represent exactly as an int and as a double.

What is the larget number of squares for which you can calculate the exact number of grains using...
- an int?
- a double?
*/

#include<iostream>
#include<cmath>
using namespace std;

int main() {


    // INTEGERS: highest square for which we can represent is 30, value = 1_073_741_824
    cout << "--------------------------------\n"
         << "Integers:\n";
    int int_total_grains_of_rice = 0;
    int int_current_square_grains_of_rice = 0;
    for(int square=0; square<64; ++square){
        int_current_square_grains_of_rice = pow(2, square);
        int_total_grains_of_rice += int_current_square_grains_of_rice;
        cout << "\t[sq " << square << "] " << int_current_square_grains_of_rice << "  |  " << int_total_grains_of_rice << "\n";
    }

    // DOUBLES: it seems to be able to calculate all the way up to square 64?
    // The numbers are monotonically increasing, at the very least.
    // The total calculated number of rice grains (18_446_744_073_709_551_616)   << This isn't right.  We are off by 1, according to wikipedia.
    //                                                                              The test below doesn't work, either, both are stuck at _616.
    cout << "--------------------------------\n"
         << "Doubles:\n"
         << fixed;
    double dbl_total_grains_of_rice = 0;
    double dbl_current_square_grains_of_rice = 0;
    for(int square=0; square<64; ++square){
        dbl_current_square_grains_of_rice = pow(2, square);
        dbl_total_grains_of_rice += dbl_current_square_grains_of_rice;
        cout << "\t[sq " << square << "] " << dbl_current_square_grains_of_rice << "  |  " << dbl_total_grains_of_rice << "\n";
    }

    double test = pow(2, 64);
    double testminus1 = pow(2, 64) - 1;
    cout << "2^64 - 1 = " << testminus1 << "\n";
    cout << "2^64     = " << test       << "\n";


    return 0;
}
