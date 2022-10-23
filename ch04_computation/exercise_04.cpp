#include<iostream>
#include<vector>
using namespace std;

int main() {

    // Introduce game to user
    cout << "Please think of a number [0, 100] for me to guess.\n\n";

    // start game
    int guess = 50;
    int guess_delta = 50;
    int guess_number = 0;
    bool guessed_user_number = false;
    char user_feedback;

    while (!guessed_user_number) {

        // increment our guess number
        ++guess_number;

          // 100 -> 50 -> 25 -> 12 -> 6 -> 3 -> 1 (don't want to go to zero)
        if (guess_delta > 1)
            guess_delta /= 2;

        // print guess to user and get feedback (y / n)
        cout << "\t[Round " << guess_number <<  "]  Here's my guess: " << guess << "\n"
             << "\tIf I've guessed your number, please input (g). "
             << "Otherwise, is your number less than " << guess << "? (y/n): ";
        cin >> user_feedback;
        cout << "\n";

        // now use the feedback to inform next guess
        switch(user_feedback){
            case 'g':
                cout << "I guessed your number in " << guess_number << " tries.  Aren't I a genius?\n";
                guessed_user_number = true;
                break;
            case 'y':
                guess -= guess_delta;
                break;
            case 'n':
                guess += guess_delta;
                break;
            default:
                cout << "Sorry, that feedback is invalid.  Let's try that again.\n";
                --guess_number;
                continue;
        }
    }

    return 0;
}
