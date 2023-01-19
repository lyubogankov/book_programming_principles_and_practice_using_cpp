/*
Adding to ex08 -
The program will throw an error if the sum of values
cannot be represented as an integer.
*/

#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    cout << "Largest expressible (signed) integer on your computer: " << INT_MAX << "\n\n";

    // obtain "N"
    int values_to_sum = 0;
    cout << "Please enter the number of values you want to sum: ";
    cin >> values_to_sum;
    if (!cin)
        throw runtime_error("Expected integer number of values to sum");

    // obtain values
    // not sure what error checking to do, other than to terminate on non-int
    cout << "Please enter a series of integers:\n";
    vector<int> values;
    for(int value; cin >> value;)
        values.push_back(value);
    
    // error check N vs series
    if (values_to_sum > values.size())
        throw runtime_error("Number of values entered is smaller than desired number of values to sum.");

    // compute sum and print
    cout << "The sum of the first " << values_to_sum << " numbers ( ";
    int sum = 0;
    for(int i=0; i<values_to_sum; i++) {
        cout << values[i] << " ";
        if (INT_MAX - sum < values[i])
            throw runtime_error("Series of values will not fit within an integer.");
        sum += values[i];
    }
    cout << ") is " << sum << ".\n\n";

    return 0;
}