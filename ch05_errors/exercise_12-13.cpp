/*
"Bulls and Cows" game

- Maintain a vector of 4 unique integers, [0, 10) that the user needs to guess (generate randomly)
- Every round, user guesses 4 integers
    - "bulls" = guessed integers that match index/value
    - "cows"  = guessed integers that match       value
    - Program prints out "x bulls, y cows" unless user has guessed the number.

Also -- implement error handling!
*/


#include <iostream>
#include <random>  // for random number generation
#include <vector>
using namespace std;

/*  (from std_lib_facilities.h) random number generators. See 24.7.  */
inline default_random_engine& get_rand()
{
	static default_random_engine ran;	// note: not thread_local
	return ran;
};
inline void seed_randint(int s) { get_rand().seed(s); }
// Generates random numbers within range [min, max], it's inclusive of max.
inline int randint(int min, int max) { return uniform_int_distribution<>{min, max}(get_rand()); }
inline int randint(int max) { return randint(0, max); }

// My code
int main() {

    // Greet user, seed random number generator
    cout << "\n=== BULLS AND COWS"
         << "\n  Please enter an integer to seed random number generator: ";
    int seed_int = 0;
    cin >> seed_int;
    if (!cin)
        throw runtime_error("Expected integer, but did not receive an integer - quitting.");
    seed_randint(seed_int);

    // setup - generate the random four numbers
    constexpr int DIGITS_TO_GUESS = 4;
    vector <int> to_be_guessed = {};
    for( int i=0; i<DIGITS_TO_GUESS; i++)
        to_be_guessed.push_back(randint(9));

    // // test print
    // cout << "\n    ";
    // for (int digit : to_be_guessed)
    //     cout << digit;
    // cout << "\n";

    // main game loop

    cout << "\n  For every round, you are expected to enter " << DIGITS_TO_GUESS << " single-digit integers, separated by spaces as your guess.\n";

    bool guessed_number = false;
    int guess_number = 0;
    vector <int> user_guess = {};

    while (!guessed_number) {

        // obtain input from user with error checking
        user_guess.clear();
        cout << ": ";
        for(int value; cin >> value;)
            user_guess.push_back(value);
        if (user_guess.size() != DIGITS_TO_GUESS) {
            cout << "  Invalid number of integers entered - please enter " << DIGITS_TO_GUESS << " integers, not " << user_guess.size() << "\n  Please try again.\n";
            continue;
        }
        guess_number++;

        // compare user's guess to the "to_be_guessed" vector and compute bull/cow-numbers
        int bull_count = 0;
        int cow_count = 0;

        // if same number
        cout << "  You guessed the correct number in " << guess_number << " tries!\n\n";
        break;

        cout << "[" << guess_number << "] " << bull_count << " bulls & " << cow_count << " cows.\n\n";
        
    }

    return 0;
}