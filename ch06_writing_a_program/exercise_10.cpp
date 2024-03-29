/*

Permutation = P(a, b) =  a! / (a-b)!

Combination = C(a, b) = P(a, b) / b!

10.
Design a program that asks users for two numbers, asks them whether they want to calculate permutations or combinations, and prints out the result.
This will have several parts. Do an analysis of the above requirements. Write exactly what the program will have to do.
Then, go into the design phase. Write pseudo code for the program, and break it into sub-components.
This program should have error checking. Make sure that all erroneous inputs will generate good error messages.


Analysis:
1. Greet user, explain the perm/comb calculator
2. Input loop
    * Ask for permutation, combination, quit
        * if quit, exit
        ~ check for invalid input?
    * Ask for number of options (a) -- must be integer [1, 22]
    * Ask for number of choices (b) -- must be integer [1,  a]
        ~ check for invalid input?
    * calculate perm or comb, then print to screen!

Design:
    Functions:
        factorial()
        permutation()
        combination()
*/

#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

constexpr auto MAX_CIN_COUNT = std::numeric_limits<std::streamsize>::max();

unsigned long long int factorial(int n) {
    if (n == 0)
        return 1;
    unsigned long long int result = 1;
    for (int i=n; i > 1; i--)
        result *= i;
    return result;
}

int obtain_integer_within_bounds(int lower_inclusive, int upper_inclusive, string message) {
    cout << message << '\n'
         << "Requirements: must be an integer within the range [" << lower_inclusive << ", " << upper_inclusive << "]\n"
         << "> ";
    bool valid_input = false;
    int input;
    while (!valid_input) {
        cin >> input;
        if (lower_inclusive <= input && input <= upper_inclusive) return input;
        else if (input < lower_inclusive) cout << "Your input is too low."  << '\n' << "> ";
        else if (input > upper_inclusive) cout << "Your input is too high." << '\n' << "> ";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(MAX_CIN_COUNT, '\n');
            cout << "> ";
        }
    }
}

bool string_in_strvector(vector<string> haystack, string needle) {
     for (string s : haystack) {
          if (s == needle)
               return true;
     }
     return false;
}

int main() {

    // greet
    cout << "Welcome to the permutation / combination calculator!\n"
         << "We can perform these calculations with integers as large as 22.\n\n";

    // input loop
    vector<string> valid_selections_perm = {"p", "perm", "permutation"};
    vector<string> valid_selections_comb = {"c", "comb", "combination"};
    vector<string> valid_selections_quit = {"q", "quit"};
    string selection;
    int argument;
    bool combination = false;
    
    while (true) {

        // what does the user want to do?
        cout << "Please enter what you wish to calculate (letters in parens are shortcuts):\n"
             << "    ((p)erm)utation\n"
             << "    ((c)omb)ination\n"
             << "     (q)uit\n"
             << "> ";
        cin >> selection;

        if      (string_in_strvector(valid_selections_quit, selection)) break;
        else if (string_in_strvector(valid_selections_comb, selection)) combination = true;
        else if (string_in_strvector(valid_selections_perm, selection)) combination = false;
        else {
            cout << "\nInvalid selection: " + selection + "\nPlease try again.\n\n";
            continue;
        }

        // obtain two integers from user: a, b (that satisfy certain constraints)
        int a = obtain_integer_within_bounds(1, 20, "Please enter 'a', the number of options for selection.");
        int b = obtain_integer_within_bounds(0, a,  "Please enter 'b', the number of items to select.");

        // perform calculation (perm or comb) and display to user
        auto result = factorial(a) / factorial(a-b);
        if (combination) {
            result /= factorial(b);
            cout << "C(";
        }
        else
            cout << "P(";
        cout << a << ", " << b << ") = " << result << "\n\n";
    }

    return 0;
}