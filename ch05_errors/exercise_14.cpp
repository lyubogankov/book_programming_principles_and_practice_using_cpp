/*
Read (day-of-the-week, value) pairs from std-in.

- Collect all the values for each day of the week in a vector<int>.
- Write out the values of the seven day-of-the-week vectors.
- Print the sum of the values in each vector.
- Ignore illegal days, but accept common synonyms such as "Monday" <- "Mon", "monday"
- Write out the number of rejected values.

Also -- error checking!
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {

    // setup
    vector<vector<int>> day_of_week_values = {{}, {}, {}, {}, {}, {}, {}};
    int rejected_values = 0;

    cout << "Please enter (day-of-the-week, integer-value) pairs.  Press CTRL-C to quit.\n\n";

    // input loop
    string dayofweek;
    int value;
    while (true) {

        cout << "----------------------------------------------------------------------------------\n";
        cin >> dayofweek >> value;
        cout << "\n";

        // process inputs
        if (     dayofweek == "Monday"    || dayofweek == "monday"    || dayofweek == "Mon"   || dayofweek == "mon"  )
            day_of_week_values[0].push_back(value);
        else if (dayofweek == "Tuesday"   || dayofweek == "tuesday"   || dayofweek == "Tues"  || dayofweek == "tues" )
            day_of_week_values[1].push_back(value);
        else if (dayofweek == "Wednesday" || dayofweek == "wednesday" || dayofweek == "Wed"   || dayofweek == "wed"  )
            day_of_week_values[2].push_back(value);
        else if (dayofweek == "Thursday"  || dayofweek == "thursday"  || dayofweek == "Thurs" || dayofweek == "thurs")
            day_of_week_values[3].push_back(value);
        else if (dayofweek == "Friday"    || dayofweek == "friday"    || dayofweek == "Fri"   || dayofweek == "fri"  )
            day_of_week_values[4].push_back(value);
        else if (dayofweek == "Saturday"  || dayofweek == "saturday"  || dayofweek == "Sat"   || dayofweek == "sat"  )
            day_of_week_values[5].push_back(value);
        else if (dayofweek == "Sunday"    || dayofweek == "sunday"    || dayofweek == "Sun"   || dayofweek == "sun"  )
            day_of_week_values[6].push_back(value);
        else
            rejected_values++;

        // print status
        for (int i=0; i < 7; i++) {
            switch(i) {
                case 0: cout << "Monday:    "; break;
                case 1: cout << "Tuesday:   "; break;
                case 2: cout << "Wednesday: "; break;
                case 3: cout << "Thursday:  "; break;
                case 4: cout << "Friday:    "; break;
                case 5: cout << "Saturday:  "; break;
                case 6: cout << "Sunday:    "; break;
            }
            // print all values and their sum
            int sum = 0;
            cout << "\n  Sum( ";
            if (day_of_week_values[i].size() > 0) {
                for (int value : day_of_week_values[i]) {
                    cout << value << " ";
                    sum += value;
                }
            }
            cout << ") = " << sum << "\n";
        }
        cout << "Rejected entries: " << rejected_values << "\n";
    }

    return 0;
}