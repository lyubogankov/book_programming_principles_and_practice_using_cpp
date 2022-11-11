/*
Create a program to find all prine numbers between 1 and 100.

One way to do this is to write afunction that will check if a number is prime
  (see if the number can be divided by a prime number smaller than itself) using a vector of primes in order.
  (ex: primes[0] == 2, primes[1] = 3, primes[2] == 5, etc.)

Then write a loop that goes from 1->100, checks each number to see if it is a prime, and stores each prime found in a vector.
Write another loops that lists the primes you found.
*/

#include<iostream>
#include<vector>
using namespace std;

constexpr int N = 100000;

inline bool is_prime(int n, vector<int> found_primes) {
    // Definition of a prime number:  it is not divisible by numbers other than 1 and itself.
    // Therefore, if we are able to find a number i smaller than n that is evenly divisible
    // into n (n % i is 0, no remainder) then n is not a prime.

    // *time measurements using "time ./a.out" on linux mint.

    // N = 100_000, took 0.65s!
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

    // N = 100_000, took ~1.5s -- this method is definitely slower!
    // for(int i=2; i<n; ++i){
    //     if (n % i == 0 && i < n)
    //         return false;
    // }
    return true;
}

int main() {

    // find all the prime numbers between 1 and 100
    vector<int> found_primes;
    for(int i=2; i<=N; ++i){
        if (is_prime(i, found_primes) == true){
            found_primes.push_back(i);
        }
    }
    cout << "Here are the primes I found:\n";
    for (int prime : found_primes)
        cout << "\t" << prime << "\n";

    return 0;
}
