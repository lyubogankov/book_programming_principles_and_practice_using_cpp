/*
Modify exercise 11 to take an input value (integer) and find the prime numbers from 1->input.
*/

#include<iostream>
#include<vector>
using namespace std;

inline bool is_prime(int n) {
    // Definition of a prime number:  it is not divisible by numbers other than 1 and itself.
    // Therefore, if we are able to find a number i smaller than n that is evenly divisible
    // into n (n % i is 0, no remainder) then n is not a prime.

    // However, as the book notes, a  faster method is to check all prior prime numbers and see
    // if our current number is divisible by any known primes smaller than it.

    if (found_primes.size() > 0) {
        for (int prime : found_primes)
            if (n % prime == 0)
                return false;
    } else {
        for(int i=2; i<n; ++i){
            if (n % i == 0 && i < n)
                return false;
        }
    }
    return true;
}

int main() {

    cout << "Please input a positive integer number greater than 1.\n"
         << "This program will calculate all prime numbers between 1 and your number: ";
    int user_max;
    cin >> user_max;

    // int user_max = 10000000;

    // find all the prime numbers between 1 and <N>
    vector<int> found_primes;
    for(int i=2; i<=user_max; ++i){
        if (is_prime(i) == true){
            found_primes.push_back(i);
        }
    }
    cout << "Here are the primes I found:\n";
    for (int prime : found_primes)
        cout << "\t" << prime << "\n";
    cout << "Number of primes: " << found_primes.size() << "\n\n";

    return 0;
}
