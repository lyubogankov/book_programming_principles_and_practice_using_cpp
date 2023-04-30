/*
7. Read five names into a vector<string> name, then prompt the user
   for the ages of the people named and store the ages in a vector<double> age.
   
   Then print out the five (name[i],age[i]) pairs.
   Sort the names (sort(name.begin(),name.end())) and print out the (name[i],age[i]) pairs.
   
   The tricky part here is to get the age vector in the correct order to match the sorted name vector.
   Hint: Before sorting name, take a copy and use that to make a copy of age in the right order after sorting name.

        In Python, I could...
        - put name/age pairs into tuples and sort the list of tuples
        - make a dictionary of name -> age and use that to look up ages

8. Then, do that exercise again but allowing an arbitrary number of names.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    vector<string> names;
    vector<string> original_name_order;
    vector<double> ages;

    string name_input = "";
    cout << "Please input names (type 'quit' once done):\n";
    while(true) {
        cout << "> ";
        cin >> name_input;
        if(name_input == "quit") break;
        names.push_back(name_input);
        original_name_order.push_back(name_input);
    }

    int age_input = 0;
    for (string name : names) {
        cout << "How old is " << name << "? ";
        cin >> age_input;
        ages.push_back(age_input);
    }

    
    // sort names
    sort(names.begin(), names.end());

    // figure out sorted order of ages
    vector<int> sorted_ages;
    for (int i=0; i<names.size(); i++) {
        // look up current name from sorted
        // scan through the original order name/age pairs
        // append age to sorted vector
        for (int j=0; j<ages.size(); j++) {
            if (names[i] == original_name_order[j]) {
                sorted_ages.push_back(ages[j]);
                break;
            }
        }
    }

    // printing
    cout << "Sorted output:\n";
    for (int i=0; i<names.size(); i++) {
        cout << "  (" << names[i] << ", " << sorted_ages[i] << ")\n";
    }

    return 0;
}