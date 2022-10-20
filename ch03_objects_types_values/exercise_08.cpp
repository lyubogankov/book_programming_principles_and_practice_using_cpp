#include<iostream>
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int val = 0;
    cin >> val;
    cout << "The integer " << val << " is ";
    if (val % 2 == 0)
        cout << "even";
    else
        cout << "odd";
    cout << ".\n";
}
