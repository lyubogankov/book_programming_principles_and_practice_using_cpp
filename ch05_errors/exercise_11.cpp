/*
Write a program that writes out values in the fibonacci sequence
until they can no longer be stored in an integer.
*/

#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<int> fib_numbers = {1, 1};

    int fib_count = 1;
    while (true) {
        
        // find next fib num
        int fib_minus_one = fib_numbers[fib_numbers.size() - 1];
        int fib_minus_two = fib_numbers[fib_numbers.size() - 2];
        if (INT_MAX - fib_minus_one < fib_minus_two)
            break;
        int next_fib = fib_minus_one + fib_minus_two;
        fib_numbers.push_back(next_fib);

        fib_count += 1;
        if (fib_count < 10)
            cout << "Fibonacci number #0" << fib_count << " is " << next_fib << "\n";
        else
            cout << "Fibonacci number #"  << fib_count << " is " << next_fib << "\n";
    }
    
    return 0;
}