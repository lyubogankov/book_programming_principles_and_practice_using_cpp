#include<iostream>
using namespace std;

template <class T> const T& evaluate_operations(const T& val1, const T& val2);
template <class T> const T& evaluate_operations(const T& val1, const T& val2) {
    cout << "min:  " << min(val1, val2) << "\n"  // std::min
         << "max:  " << max(val1, val2) << "\n"  // std::max
         << "sum:  " << val1 + val2     << "\n"
         << "diff: " << val1 - val2     << "\n"
         << "prod: " << val1 * val2     << "\n"
         << "div:  " << val1 / val2     << "\n"; // can be different between int/double
}

int main() {
    double val1=0.0, val2=0.0;
    cout << "Please enter two double values: ";
    cin >> val1 >> val2;
    evaluate_operations(val1, val2);

    cout << "\n\nNow trying this with the same values, cast as integers: \n";
    evaluate_operations((int)val1, (int)val2); // using explicit type casting!
    // cout << "min:  " << min(val1, val2) << "\n"  // std::min
    //      << "max:  " << max(val1, val2) << "\n"  // std::max
    //      << "sum:  " << val1 + val2     << "\n"
    //      << "diff: " << val1 - val2     << "\n"
    //      << "prod: " << val1 * val2     << "\n"
    //      << "div:  " << val1 / val2     << "\n"; // can be different between int/double
}
