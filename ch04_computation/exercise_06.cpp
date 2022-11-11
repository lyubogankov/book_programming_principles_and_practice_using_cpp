/*
Make a vector holding ten string values "zero", "one", ..., "nine".
Use it in a program that converts a digit to its corresponding spelled-out value (input 7 -> output "seven").
Additionally, program must also accept spelled-out digits and output digit       (input "seven" -> output 7).
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {

    vector<string> digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    string user_input;
    while(cin >> user_input) {

        // if the input is a digit
        // if (user_input == "0" || user_input == "1" || user_input == "2" || user_input == "3" || user_input == "4" || user_input == "5" || user_input == "6" || user_input == "7" || user_input == "8" || user_input == "9")
        if(user_input[0] >= 48 && user_input[0] <= 57 && user_input.size() == 1)
            cout << digits[stoi(user_input)]; // stoi() was apparently introduced in c++11
        else {
            for(int i=0; i<digits.size(); ++i){
                if (user_input == digits[i]){
                    cout << i;
                    break;
                }
            }
        }
        cout << "\n\n";

    }

    return 0;
}
