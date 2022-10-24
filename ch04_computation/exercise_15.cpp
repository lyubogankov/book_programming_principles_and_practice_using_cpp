#include<iostream>
#include<limits>
#include<vector>
using namespace std;

/*
The Sieve of Erathosthenes  (https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)

To find all the prime numbers less than or equal to a given integer n by Eratosthenes' method:
  1.  Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
  2.  Initially, let p equal 2, the smallest prime number.
  3.  Enumerate the multiples of p by counting in increments of p from 2p to n, and mark them in the list (these will be 2p, 3p, 4p, ...; the p itself should not be marked).
  4.  Find the smallest number in the list greater than p that is not marked.
      If there was no such number, stop
      Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.

When the algorithm terminates, the numbers remaining not marked in the list are all the primes below n.
The main idea here is that every value given to p will be prime, because if it were composite it would be marked as a multiple of some other, smaller prime.
Note that some of the numbers may be marked more than once (e.g., 15 will be marked both for 3 and 5).
*/

/*
This implimentation is more complicated than I originally intended.

At first, I wanted to set the largest integer for which to run the sieve to the largest possible int (numeric_limits<int>::max())
but found the program ran WAY too slowly.

The solution was to introduce complexity - do multiple passes over the sieve, increasing the max search integer each
time.  The nice thing is that we don't need to start from scratch for the 2nd iteration onwards - we have our work
from all prior iterations, so we are just computing the new values.  It runs pretty quickly!
*/

int main() {

    cout << "Please input the number of primes you would like me to find (positive integer, please): ";
    int n;
    cin >> n;

    // int max_search_int = numeric_limits<int>::max()  // tried this -- way too slow.
    int max_search_int = 10;
    vector<int> primes_found = {2};

    // set up all needed variables
    vector<int> integers          = {};
    vector<bool> integer_markings = {};
    int last_prime_found, p, next_p;

    while (primes_found.size() < n) {

        // overarching loop - either running SoE for first time, or extending existing work.
        last_prime_found = primes_found[primes_found.size() - 1];
        max_search_int *= 10; // multiplying our search range by factor of 10 each time. (max_search_int = 100, 1_000, 10_000, ...)

        // 1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
        //    Start at the last prime found, but keep our work from last pass over integers/integer_markings.
        for(int i=last_prime_found; i<=max_search_int; ++i){
            integers.push_back(i);
            integer_markings.push_back(false); // marked = true = not a prime, we're initializing false.
        }

        // 2. Initially, let p equal 2, the smallest prime number.
        //    Modified: for subsequent passes, set to last prime found.  Pass 1, last prime = 2.
        p = 0;
        next_p = last_prime_found;

        while (p != next_p && primes_found.size() < n){

            // Updating p -- this loop will keep going until we can no longer update next_p in then
            // for loop in step 4 and next_p will equal p in the condition above.
            p = next_p;

            // 3.  Enumerate the multiples of p by counting in increments of p from 2p to n,
            //     and mark them in the list (these will be 2p, 3p, 4p, ...; the p itself should not be marked).
            for(int i=2*p; i<=max_search_int; i += p){
                integer_markings[i-2] = true;  // adjusting -- vector goes from 2 -> n, so 0th element is 2.
            }

            // 4. Find the smallest number in the list greater than p that is not marked.
            //    If there was no such number, stop.
            //    Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.
            for(int i = p+1; i<=max_search_int; i++){
                if (integer_markings[i-2] == false) {  // adjusting -- vector goes from 2 -> n, so 0th element is 2.
                    next_p = i;
                    primes_found.push_back(next_p);
                    break;
                }
            }
        }
    }

    // When the algorithm terminates, the numbers remaining not marked in the list are all the primes below n.
    cout << "Here are the first " << n << " primes I've found:\n";
    int number_of_primes = 0;
    for(int i=0; i<integer_markings.size(); ++i){
        if (integer_markings[i] == false){
            cout << "\t" << integers[i] << "\n";
            ++number_of_primes;
        }
        if (number_of_primes == n)
            break;
    }

    return 0;
}
