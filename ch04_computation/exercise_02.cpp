/*
Write a program (based on ch4, example 6.3) that prints out the median of a sequence.
Note that a median need not be an element of the sequence!
*/

#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<double> temps;

    // read in raw data
    for(double temp; cin >> temp;)
        temps.push_back(temp);


    // sort(temps);  // Question - it was presented in the book like this, but compiler throws error.
    sort(temps.begin(), temps.end());
    cout << "Sorted temps (" << temps.size() << "): ";
    for (double t : temps)
        cout << "    " << t;
    cout << "\n";

    // compute median temperature -- original
    cout << "Median temperature: " << temps[temps.size()/2] << "\n";
    // compute median temperature -- updated
    cout << "Updated median temp: ";
    int naiive_median_idx = temps.size() / 2;
    // vector with odd # elements always a median element
    if (temps.size() % 2 == 1)
        cout << temps[naiive_median_idx] << "\n";
    // vector with even # elements never has median element - calc avg of two nearest elements
    else {
        double element_below_median = temps[naiive_median_idx - 1];
        double element_above_median = temps[naiive_median_idx    ];
        cout << (element_above_median + element_below_median) / 2.0 << "\n";
    }

    return 0;
}
