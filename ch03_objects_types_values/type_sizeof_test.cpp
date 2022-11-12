#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

int main() {

    cout << std::fixed;

    // CHAR - 1 byte
    cout << "Size of char: " << sizeof(char) << " byte\n";

    // INT - 4 bytes
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "\t Largest int, assuming signed: +" << int(pow(2, 8*4)/2 - 1)      << "\n"
         << "\t            vs numeric_limits: +" << numeric_limits<int>::max()  << "\n\n";
    cout << "\tSmallest int, assuming signed: "  << int((-1*pow(2, 8*4)/2))     << "\n"
         << "\t            vs numeric_limits: "  << numeric_limits<int>::min()  << "\n\n";

    // FLOAT - 4 bytes
    cout << "Size of float: " << sizeof(float) << " bytes\n";

    // DOUBLE - 8 bytes
    cout << "Size of doubel: " << sizeof(double) << " bytes\n";

    // cout << "Size of double: " << sizeof(double) << " bytes\n";
    // cout << "\t Largest double, assuming signed: +" << pow(2, 8*8)/2 << "\n";
    // cout << "\tSmallest double, assuming signed: " << (-1*pow(2, 8*8)/2) + 1  << "\n";

    cout << "---\n";

    cout << "Double limits, according to <limits>:\n";
    cout << "\t Largest double, assuming signed: +" << numeric_limits<double>::max() << "\n";
    cout << "\tSmallest double, assuming signed: "  << numeric_limits<double>::lowest() << "\n";

    cout << "---\n";

    cout << "Truing out the limits:\n";
    double largest_double = pow(2, 8*8)/2;
    double largest_double_plus_one = largest_double + 1;
    cout << "\t Largest signed double:     +" << largest_double << "\n";
    cout << "\t Largest signed double + 1: +" << largest_double_plus_one << "\n";
    double smallest_double = (-1*pow(2, 8*8)/2) + 1;
    double smallest_double_minus_one = smallest_double - 1;
    cout << "\tSmallest signed double:     " << smallest_double << "\n";
    cout << "\tSmallest signed double - 1: " << smallest_double_minus_one << "\n";

    cout << "---\n";

    // //         2147483648
    // constexpr double x = 3000000000;
    // int y = x;
    //
    // cout << "Original double: +" << x << "\n";
    // cout << "   Narrowed int: " << y << "\n";
    //
    // // take 2 - using the notation
    //
    // int z {x};
    // cout << "Original double: +" << x << "\n";
    // cout << "   Narrowed int: " << z << "\n";

    return 0;
}
