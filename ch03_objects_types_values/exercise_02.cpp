#include<iostream>
using namespace std;

int main() {
    double miles = -1.0;
    cout << "miles -> kilometers converter\n"
         << "Please enter number of miles: ";
    cin >> miles;
    cout << miles*1.609  << "km!\n\n";
}
