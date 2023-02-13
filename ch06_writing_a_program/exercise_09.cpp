/*
 9. Write a program that reads digits and composes them into integers. 
 
    For example, 123 is read as the characters 1, 2, and 3. The program should output 123 is 1 hundred and 2 tens and 3 ones.
    The number should be output as an int value. Handle numbers with one, two, three, or four digits.
    
    Hint: To get the integer value 5 from the character '5' subtract '0', that is, '5'–'0'==5.
*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

    cout << "Please enter an integer number, and any other character to conclude the integer.\n"
         << "Enter an 'x' to quit.\n\n";

    vector<int> digits;
    vector<string> pos = {"one", "ten", "hundred"};
    vector<string> pos_later = {"thousand", "million", "billion", "trillion"};
    vector<string> pos_later_prefix = {"", "ten-", "hundred-"};
    char input;

    while(true) {

        digits.clear();  // clear out contents from last loop, if any
        // 1. input loop - obtain integer as char sequence, check for quit
        while (cin >> input) {
            if (input == 'x')
                return 0;
            if (input > '9' || input < '0')
                break;
            digits.push_back(input - '0');  // turn input from ASCII char -> integer!
            // switch (input) {
            // case 'x':
            //     return 0;
            // case '0': case '1': case '2': case '3': case '4':
            // case '5': case '6': case '7': case '8': case '9':
            //     digits.push_back(input - '0');  // turn input from ASCII char -> integer!
            //     break;
            // default:
            //     break;
            // }
        }

        // 2. print out the integer I got, also the "places" of each digit
        //    Calculating the integer only works within the size of the long-long int!
        unsigned long long int total = 0;
        int place = pow(10, digits.size()-1);
        string pos_signifier = "";
        int idx;
        for (int i=0; i<digits.size(); i++) {
            idx = digits.size() - 1 - i;
            // construct pos signifier
            if (idx < 3)
                pos_signifier = pos[idx];
            else
                pos_signifier = pos_later_prefix[(idx-3) % 3] + pos_later[(idx-3) / 3];
            if (digits[i] != 1)
                pos_signifier += "s";
            if (digits[i] != 0) {
                // print to user
                if (i > 0)
                    cout << " and ";
                cout << digits[i] << " " << pos_signifier;
            }
            // update the number
            total += place * digits[i];
            place /= 10;
        }
        cout << "\nNumber you entered as a ull_int:\n" << total;
        cout << "\nNumber you entered as sequence of chars:\n";
        for (int d : digits)
            cout << char(d + '0');
        cout << "\n\n";
    }
}