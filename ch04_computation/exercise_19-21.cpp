/*
ex19
Write a program where you first enter a set of name-and-value pairs, such as "Joe 17" and "Barbara 22".
For each pair, add the name to a vector called names and the number to a vector called scores.
Terminate input with "NoName 0".  Check that each name is unique and terminate with an error message
if a name is entered twice.  Write out all the (name,score) pairs, one per line.

ex20
Modify ex19 so that when you enter a name, the program will output the corresponding score or "Name not found."

ex21
Modify ex19 so that when you enter an integer, the program will output all names with that score or "score not found."
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {

    // constexpr int exercise = 19;  // 19, 20, 21

    vector<string> names;
    vector<int> scores;
    string name="";
    int score=0;

    // input loop
    cout << "Please enter a set of name-and-value pairs of the form {name} {value} (ex: Joe 17).\n"
         << "Note: names must be unique!\n"
         << "When you are done entering name-value pairs, please enter NoName 0 to terminate entry.\n\n";
    while(true) {
        cin >> name >> score;
        if (name == "NoName" && score == 0)
            break;
        // ex 19 - detect duplicate names
        for (string n : names) {
            if (n == name) {
                cout << "Error - duplicate name entered.  Terminating program.\n";
                return 0;
            }
        }
        names.push_back(name);
        scores.push_back(score);
    }

    // ex 19 - print out all the name-and-value pairs
    cout << "\n\n"
         << "Here are all the name, value pairs you entered:\n";
    for (int i=0; i<names.size(); ++i) {
        cout << "\t(" << names[i] << ", " << scores[i] << ")\n";
    }


    bool found; // used for ex20 and ex21

    // ex 20 - allow user to query names, and get back scores (terminate with NoName)
    cout << "\nNow that you've entered all the names, you may search for a given name and get back the score, if extant."
         << "\nType NoName to terminate."
         << "\n";
    while(true) {
        cin >> name;
        if (name == "NoName")
            break;
        found = false;
        for (int i=0; i<names.size(); ++i) {
            if (names[i] == name) {
                cout << "score: " << scores[i] << "\n\n";
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Name not found.\n\n";
    }

    // ex 21 - allow user to query scores, and get back names (terminate with non-integer)
    cout << "You also have the option to search for scores and get back names.  Enter a non-integer to terminate.\n";
    while (cin >> score) {
        found = false;
        vector<string> found_names;
        for (int i=0; i<scores.size(); ++i) {
            if (scores[i] == score) {
                found_names.push_back(names[i]);
                found = true;
            }
        }
        if (found) {
            for (int i=0; i<found_names.size(); ++i) {
                cout << found_names[i];
                if (i < found_names.size() - 1)
                    cout << ", ";
                else
                    cout << "\n";
            }
        } else
            cout << "Score not found.\n\n";
    }

    // All done.
    cout << "Farewell!\n\n\n";
    return 0;
}
