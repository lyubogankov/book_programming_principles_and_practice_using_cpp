/*
6. This chapter does not say what happens when you run out of memory using new. That’s called memory exhaustion.
   Find out what happens. You have two obvious alternatives: look for documentation, 
   or write a program with an infinite loop that allocates but never deallocates. Try both.
   Approximately how much memory did you manage to allocate before failing?



   Table with binary unit names: https://web.njit.edu/~walsh/powers/
*/

#include <limits.h>
#include <iostream>
#include <random>
using namespace std;

int main() {

    unsigned long long int counter = 0;
    default_random_engine e1(1); // seeding with a constant for repeatable generation
    uniform_int_distribution<int> uniform_dist_int(INT_MIN, INT_MAX);

    // memory exhaustion
    // first attempt: only printing out counts divisible by 1024.
    //  The program was "killed" by the OS
    //      Last printout = 225278976 counts * 4bytes/int = 901115904 bytes
    //                                                    = 879996       Kilobytes (2^10 bytes, 1024)
    //                                                    = 859.37109375 Megabytes (2^20 bytes)
    //                                                    = 0.839229584  Gigabytes (2^30 bytes)
    // second attempt: only printing out counts greater than or equal to ~first limit.
    //  I had to manually kill the program because it was hanging my computer.
    //      Last printout = 226000653 counts * 4bytes/int = 904002612 bytes = 0.84191804 GB.
    while (true) {
        int* p = new int;           // create new integer
        *p = uniform_dist_int(e1);  // assign it a value
        counter++;
        // // Attempt 1
        // if (counter % 1024 == 0)
        //     cout << counter << '\n';
        // Attempt 2
        if (counter > 225274880)
            cout << counter << '\n';
    }

    return 0;
}