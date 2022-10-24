#include<iostream>
#include<vector>
using namespace std;

inline bool is_prime(int n) {
    // Definition of a prime number:  it is not divisible by numbers other than 1 and itself.
    // Therefore, if we are able to find a number i smaller than n that is evenly divisible
    // into n (n % i is 0, no remainder) then n is not a prime.
    for(int i=2; i<=n; ++i){
        if (n % i == 0 && i < n)
            return false;
    }
    return true;
}

int main() {

    // find all the prime numbers between 1 and 100
    vector<int> found_primes;
    for(int i=2; i<=100; ++i){
        if (is_prime(i) == true){
            found_primes.push_back(i);
        }
    }
    cout << "Here are the primes I found:\n";
    for (int prime : found_primes)
        cout << "\t" << prime << "\n";

    return 0;
}
