#include<iostream>
using namespace std;

int main() {
    int val1=0, val2=0;
    cout << "Please enter two integer values: ";
    cin >> val1 >> val2;
    cout << "min:  " << min(val1, val2) << "\n"  // std::min
         << "max:  " << max(val1, val2) << "\n"  // std::max
         << "sum:  " << val1 + val2     << "\n"
         << "diff: " << val1 - val2     << "\n"
         << "prod: " << val1 * val2     << "\n"
         << "div:  " << val1 / val2     << "\n";
}
