/*
Find all prime numbers 1->100 (ex13) and 1->user_input_max (ex14) using the "Sieve of Eratosthenes".
*/

#include<iostream>
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

int main() {

    cout << "Please input a positive integer number greater than 1.\n"
         << "I will calculate all prime numbers between 1 and your number: ";
    int n;
    cin >> n;

    // int n = 10000000;

    // 1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
    vector<int> integers;
    vector<bool> integer_markings;
    for(int i=2; i<=n; ++i){
        integers.push_back(i);
        integer_markings.push_back(false); // marked = true = not a prime, we're initializing false.
    }

    // 2. Initially, let p equal 2, the smallest prime number.
    int p = 0;
    int next_p = 2;

    while (p != next_p){

        // Updating p -- this loop will keep going until we can no longer update next_p in then
        // for loop in step 4 and next_p will equal p in the condition above.
        p = next_p;

        // 3.  Enumerate the multiples of p by counting in increments of p from 2p to n,
        //     and mark them in the list (these will be 2p, 3p, 4p, ...; the p itself should not be marked).
        for(int i=2*p; i<=n; i += p){
            integer_markings[i-2] = true;  // adjusting -- vector goes from 2 -> n, so 0th element is 2.
        }

        // 4. Find the smallest number in the list greater than p that is not marked.
        //    If there was no such number, stop.
        //    Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.
        for(int i = p+1; i<=n; i++){
            if (integer_markings[i-2] == false) {  // adjusting -- vector goes from 2 -> n, so 0th element is 2.
                next_p = i;
                break;
            }
        }
    }

    // When the algorithm terminates, the numbers remaining not marked in the list are all the primes below n.
    cout << "Here are the primes I've found:\n";
    int number_of_primes = 0;
    for(int i=0; i<integer_markings.size(); ++i){
        if (integer_markings[i] == false){
            cout << "\t" << integers[i] << "\n";
            ++number_of_primes;
        }
    }
    cout << "Number of primes between 1 and " << n << ": " << number_of_primes << "\n";

    return 0;
}
