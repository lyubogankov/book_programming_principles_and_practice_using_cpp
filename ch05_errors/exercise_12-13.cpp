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
#include <limits>
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

constexpr auto MAX_CIN_COUNT = std::numeric_limits<std::streamsize>::max();

// setup - generate random numbers and ensure they are unique
//      If MAX_INTEGER is a non-negative integer, 
//      then there are MAX_INTEGER possible digits,
//      so that is the max value for DIGITS_TO_GUESS.
constexpr int MAX_INTEGER = 9;
constexpr int DIGITS_TO_GUESS = 4;

void print_vector_elements(vector<int> v) {
    for (int digit : v)
        cout << digit << " ";
    cout << "\n";
}

bool value_in_vector(int val, vector<int> v) {
    for (int x : v) {
        if (x == val)
            return true;
    }
    return false;
}

vector<int> generate_digits_to_be_guessed() {
    if (DIGITS_TO_GUESS > MAX_INTEGER + 1)
        throw runtime_error("Program constants picked incorrectly - DIGITS_TO_GUESS must be <= MAX_INTEGER + 1");

    vector <int> to_be_guessed = {};    
    while (to_be_guessed.size() < DIGITS_TO_GUESS) {
        int x = randint(9);
        if (value_in_vector(x, to_be_guessed))
            continue;
        to_be_guessed.push_back(x);
    }
    // print_vector_elements(to_be_guessed);  // test print
    return to_be_guessed;
}

int main() {

    // Greet user, seed random number generator
    cout << "\n=== BULLS AND COWS"
         << "\n  Please enter an integer to seed random number generator: ";
    int seed_int = 0;
    cin >> seed_int;
    if (!cin)
        throw runtime_error("Expected integer, but did not receive an integer - quitting.");
    seed_randint(seed_int);
    // obtain digits
    vector<int> to_be_guessed = generate_digits_to_be_guessed();

    // main game loop
    cout << "\n  For every round, you are expected to enter " 
         << DIGITS_TO_GUESS << " unique single-digit integers [0, 10) (press ENTER to confirm each)\n"
         << "----------\n\n\n";

    bool guessed_all_digits = false;
    int guess_count = 0;
    vector <int> user_guess;

    while (!guessed_all_digits) {

        // obtain input from user with error checking
        user_guess.clear();
        int guess;
        for (int i=0; i<DIGITS_TO_GUESS; i++) {
            cout << "(" << i+1 << "/" << DIGITS_TO_GUESS << ") ";
            // https://stackoverflow.com/a/21567292 -- ignoring leading newline
            cin >> std::ws >> guess;
            if (cin.fail()) {
                // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
                cin.clear();
                cin.ignore(MAX_CIN_COUNT, '\n');
                cout << "      ^ Not an integer!  Try again.\n";
                i--;
                continue;
            } 
            if (value_in_vector(guess, user_guess)) {
                cout << "      ^ Already been guessed during this round!  Try again.\n";
                i--;
                continue;
            }
            user_guess.push_back(guess);
        }
        guess_count++;

        // compare user's guess to the "to_be_guessed" vector and compute bull/cow-numbers
        int bull_count = 0;
        int cow_count = 0;

        for (int i=0; i < DIGITS_TO_GUESS; i++) {
            if (user_guess[i] == to_be_guessed[i])
                bull_count++;
            else if (value_in_vector(user_guess[i], to_be_guessed))
                cow_count++;
        }
        // if same number
        if (bull_count == DIGITS_TO_GUESS) {
            cout << "  You guessed the correct number in " << guess_count << " tries!\n\n";
            guessed_all_digits = true;
        } else {
            cout << "[Guess " << guess_count << "] " << bull_count << " bulls & " << cow_count << " cows.\n\n";
        }
    }

    return 0;
}