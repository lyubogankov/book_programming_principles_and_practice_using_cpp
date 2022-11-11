/*
Create a program that finds the mode of a set of positive integers.
*/

#include<vector>
#include<iostream>
using namespace std;

int main() {

    constexpr bool DEBUG = false;

    vector<int> mode_tracking_vector; // size starts at 0
    int current_int = 0;
    int prior_size = 0;
    int idx = -1;

    // Positive integers means 1 onwards (0 does not count as positive)
    // This loop terminates on a non-integer input from user.
    while (cin >> current_int) {

        idx = current_int - 1;

        if (current_int > mode_tracking_vector.size()) {
            // not sure if this is like python where I can't mutate list as a I iterate over it
            prior_size = mode_tracking_vector.size();
            for(int i=0; i<(current_int - prior_size); ++i) {
                mode_tracking_vector.push_back(0);
                if (DEBUG)
                    cout << "\t\tadded new idx to mode_tracking_vector\n";
            }
            if (DEBUG)
                cout << "\t\tnew size: " << mode_tracking_vector.size() << "\n\n";
        }
        mode_tracking_vector[idx] += 1;

        if (DEBUG) {
            cout << "\t\tmode_tracking_vector contents: ";
            for(int i=0; i<mode_tracking_vector.size(); ++i)
                cout << "(" << i << "->" << i+1 << ", " << mode_tracking_vector[i] << ") ";
            cout << "\n";
        }
    }

    // After the loop, need to print the mode!
    int max_count = -1;
    int max_count_idx = -1;  // idx = number = mode after the loop!
    int current_count = -1;
    for(int i=0; i<mode_tracking_vector.size(); ++i) {
        current_count = mode_tracking_vector[i];
        if (current_count > max_count) {
            max_count = current_count;
            max_count_idx = i;
        }
    }
    cout << "\n\n"
         << "The mode of the numbers you entered is: " << max_count_idx+1 << "  "
         << "(appeared " << max_count << " times)"
         << "\n\n";

    return 0;
}
