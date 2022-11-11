/*
Write a program that finds the min, max, and mode of a sequence of strings.
*/


/*
Idea -- start with an empty vector.
For each string seen, add a vector of length 2 to the parent vector -- 1st idx = string, 2nd idx = count.

Once user is done entering strings, traverse parent vector and find min/max/mode!
*/

#include<iostream>
#include<vector>
using namespace std;

int main() {

    constexpr bool DEBUG = false;

    // introduce the program and define the stop condition
    cout << "Please enter a sequence of strings, separated by spaces or newlines.\n"
         << "When you are done entering the strings, type please '.' (a period).\n\n";

    vector<string> raw_data_strings;  // size starts at 0
    vector<int>    raw_data_count;
    string current_input;

    string current_max="", current_min="", current_mode="";
    int current_mode_cnt = 0;
    bool seen;
    bool first_time_in_loop = true;

    // gather raw data from user
    while(cin >> current_input) {

        // is the user done entering string sequence?
        if (current_input == ".")
            break;

        // populating max/min with first string in sequence
        if (first_time_in_loop) {
            current_max = current_input;
            current_min = current_input;
            first_time_in_loop = false;
        }

        // MODE:
        // have we already seen the string the user has entered?
        seen = false;
        for(int i=0; i<raw_data_strings.size(); ++i) {
            // yes - this string has already been seen
            if (current_input == raw_data_strings[i]) {
                // increment string freq counter
                raw_data_count[i] += 1;
                // check for new mode
                if (raw_data_count[i] > current_mode_cnt) {
                    current_mode = current_input;
                    current_mode_cnt = raw_data_count[i];
                }
                seen = true;
                break;
            }
        }
        // otherwise, if we haven't already seen this - add a new entry!
        if (!seen) {
            raw_data_strings.push_back(current_input);
            raw_data_count.push_back(1);
            if (1 > current_mode_cnt) {
                current_mode = current_input;
                current_mode_cnt = 1;
            }
        }

        // Observation - max/min seem to follow ascii table.
        // aka -- lowercase letter > capital letter > digits > punctiation

        // MAX
        if (current_input > current_max)
            current_max = current_input;
        // MIN
        if (current_input < current_min)
            current_min = current_input;

        if (DEBUG)
            cout << "\n"
                 << "\tCurrent max:  " << current_max << "\n"
                 << "\tCurrent min:  " << current_min << "\n"
                 << "\tCurrent mode: " << current_mode << " (count=" << current_mode_cnt << ")\n\n";
    }

    // display to user!
    cout << "--------------\n"
         << "Overall max:  " << current_max << "\n"
         << "Overall min:  " << current_min << "\n"
         << "Overall mode: " << current_mode << " (count=" << current_mode_cnt << ")\n\n";

    return 0;
}
