#include<algorithm>
#include<iostream>
#include<limits>
#include<string>
#include<vector>
using namespace std;


// This implementation kinda meets the requirements?
// It stops on '|', as well as any other non-int...
int main() {

    // 7.
    double current_value = 0.0;
    double current_value_in_cm = 0.0;
    double current_value_in_m = 0.0;
    string current_unit = "";

    vector<double> lengths_in_m;

    int count = 0;
    double sum_in_m = 0.0;

    double smallest_seen_in_cm = numeric_limits<double>::max();  // init to  largest possible val
    double largest_seen_in_cm  = numeric_limits<double>::min();  // init to smallest possible val

    // main loop - read in value/unit pairs
    while (cin >> current_value >> current_unit) {

        // conversion to cm
        if (current_unit == "cm")
            current_value_in_cm = current_value;
        else if (current_unit == "m")   //  m -> cm
            current_value_in_cm = current_value * 100;
        else if (current_unit == "in")  // in -> cm
            current_value_in_cm = current_value * 2.54;
        else if (current_unit == "ft")  // ft -> cm
            current_value_in_cm = current_value * 12 * 2.54;
        // 8. rejection of "illegal representations of units"
        else
            continue;

        cout << "Value entered: " << current_value << current_unit;

        // 9. calculate sum, increment count
        ++count;
        current_value_in_m = current_value_in_cm / 100.0;
        sum_in_m += current_value_in_m;
        // 10. store into a vector
        lengths_in_m.push_back(current_value_in_m);

        // do the largest/smallest tabulation
        if (current_value_in_cm > largest_seen_in_cm) {
            largest_seen_in_cm = current_value_in_cm;
            cout << " (largest seen so far)";
        }
        if (current_value_in_cm < smallest_seen_in_cm) {
            smallest_seen_in_cm = current_value_in_cm;
            cout << " (smallest seen so far)";
        }
        cout << "\n\n";
    }
    // 9. Print out summary information after loop ends.
    cout << "---\n"
         << "Smallest overall: " << smallest_seen_in_cm << "cm\n"
         << " Largest overall: " << largest_seen_in_cm  << "cm\n"
         << "           Count: " << count               <<   "\n"
         << "             Sum: " << sum_in_m            <<  "m\n";
    // 10. now do the same thing, with the vector  (max/min don't seem to work, sad)
    // cout << "Smallest overall: " << min(lengths_in_m) << "\n"
    //      << " Largest overall: " << max(lengths_in_m) << "\n";
    double smallest_m = numeric_limits<double>::max();  // init to  largest possible val
    double largest_m  = numeric_limits<double>::min();  // init to smallest possible val
    double vsum = 0.0;
    cout << "---\n"
         << "All vector values:\n";

    // 11. Sorting the vector.     
    sort(lengths_in_m.begin(), lengths_in_m.end()); // in-place ascending sort between indices[i, j)

    for (double length_in_m : lengths_in_m){
        if (length_in_m > largest_m)
            largest_m = length_in_m;
        if (length_in_m < smallest_m)
            smallest_m = length_in_m;
        vsum += length_in_m;
        cout << "    " << length_in_m << "m";
    }
    int vcount = lengths_in_m.size();
    cout << "\n---\n"
         << "Vector version!\n"
         << "Smallest overall: " << smallest_m << "m\n"
         << " Largest overall: " << largest_m  << "m\n"
         << "           Count: " << vcount     <<  "\n"
         << "             Sum: " << vsum       << "m\n";

    /*
    // 6.
    double current_value = 0.0;
    double smallest_seen = numeric_limits<double>::max();  // init to  largest possible val
    double largest_seen  = numeric_limits<double>::min();  // init to smallest possible val
    while (cin >> current_value) {
        cout << "Value entered: " << current_value;
        if (current_value > largest_seen) {
            largest_seen = current_value;
            cout << " (largest seen so far)";
        }
        if (current_value < smallest_seen) {
            smallest_seen = current_value;
            cout << " (smallest seen so far)";
        }

        cout << "\n\n";
    }
    */

    // int n1=0, n2=0;           // 1 - 3
    // double n1=0.0, n2=0.0;    // 4 - 5
    // while(cin >> n1 >> n2){   // 1 - 5
        /*
        // 1.
        cout << "Two integers entered: " << n1 << " " << n2 << "\n";
        */
        /*
        // 2.
        if (n1 > n2) {
            cout << "Smaller value: " << n2 << "\n";
            cout << "Larger  value: " << n1 << "\n";
        } else {
            cout << "Smaller value: " << n1 << "\n";
            cout << "Larger  value: " << n2 << "\n";
        }
        */
        /*
        // 3.
        if (n1 > n2) {
            cout << "Smaller value: " << n2 << "\n";
            cout << "Larger  value: " << n1 << "\n";
        } else if (n2 > n1) {
            cout << "Smaller value: " << n1 << "\n";
            cout << "Larger  value: " << n2 << "\n";
        } else {
            cout << "The numbers are equal\n";
        }
        */
        // 4.
        /*
        if (n1 == n2)
            cout << "The numbers are equal\n";
        else {
            if (n1 > n2) {
                cout << "Smaller value: " << n2 << "\n";
                cout << "Larger  value: " << n1 << "\n";
            } else if (n2 > n1) {
                cout << "Smaller value: " << n1 << "\n";
                cout << "Larger  value: " << n2 << "\n";
            }

            if (abs(n1 - n2) < 0.01)
                cout << "The numbers are almost equal.\n";
        }
        */
    // }

}
