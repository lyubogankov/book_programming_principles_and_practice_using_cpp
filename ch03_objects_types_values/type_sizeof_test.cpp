#include <iostream>
#include <cmath>
using namespace std;

int main() {

    cout << std::fixed;

    cout << "Size of char: " << sizeof(char) << " byte\n";

    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "\t Largest double, assuming signed: +" << pow(2, 8*4)/2 << "\n";
    cout << "\tSmallest double, assuming signed: " << (-1*pow(2, 8*4)/2) + 1  << "\n";

    cout << "Size of float: " << sizeof(float) << " bytes\n";

    cout << "Size of double: " << sizeof(double) << " bytes\n";
    cout << "\t Largest double, assuming signed: +" << pow(2, 8*8)/2 << "\n";
    cout << "\tSmallest double, assuming signed: " << (-1*pow(2, 8*8)/2) + 1  << "\n";

    cout << "---\n";

    //         2147483648
    constexpr double x = 3000000000;
    int y = x;

    cout << "Original double: +" << x << "\n";
    cout << "   Narrowed int: " << y << "\n";

    // take 2 - using the notation

    int z {x};
    cout << "Original double: +" << x << "\n";
    cout << "   Narrowed int: " << z << "\n";

    return 0;
}
