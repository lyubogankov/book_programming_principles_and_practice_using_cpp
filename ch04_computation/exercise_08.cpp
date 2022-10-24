#include<iostream>
#include<cmath>
using namespace std;

inline int calculate_number_of_squares_until_n_grains_of_rice(int n, bool print) {

    int current_number_of_grains = 0;
    int number_of_grains_for_current_square = 0;

    for(int i=1; i<=64; ++i){
        number_of_grains_for_current_square = pow(2, i);
        current_number_of_grains += number_of_grains_for_current_square;

        if (print == true) cout << "\t\t\t[sq" << i << "] " << number_of_grains_for_current_square << " | " << current_number_of_grains << "\n";

        if (current_number_of_grains > n){
            return i;
        }
    }
}

int main() {

    cout << "Starting with one grain of rice on square 1, "
         << "and doubling the number of grains for each subsequent square, \n"
         << "here are the minimum number of squares for...\n"
         << "\t        1_000 grains: " << calculate_number_of_squares_until_n_grains_of_rice(1000,       false) << "\n"
         << "\t    1_000_000 grains: " << calculate_number_of_squares_until_n_grains_of_rice(1000000,    false) << "\n"
         << "\t1_000_000_000 grains: " << calculate_number_of_squares_until_n_grains_of_rice(1000000000, true ) << "\n"
         << "\n";

    return 0;
}
