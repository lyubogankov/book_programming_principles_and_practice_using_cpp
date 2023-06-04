/*
1. Write a program that produces the sum of all the numbers in a file of whitespace-separated integers.

11. Write a program that produces the sum of all the whitespace-separated integers in a text file.
    For example, bears: 17 elephants 9 end should output 26.
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// ex_01.txt: "1 2 3\n4\n\n5\n      10\n"
void exercise_01() {
    string inputfile = "ex_01.txt";
    ifstream ifs {inputfile};
    if (!ifs) throw runtime_error("couldn't open file.");

    int sum = 0;
    for (int i; ifs >> i;)
        sum += i;
    cout << "Sum of integers in file (" << inputfile << "): " << sum << "\n";
}

// ex_11.txt: "bears: 17 elephants 9 end\n"
void exercise_11(bool print=false) {
    string inputfile = "ex_11.txt";
    ifstream ifs {inputfile};
    if (!ifs) throw runtime_error("couldn't open file.");

    int sum = 0;
    for (string s; ifs >> s;) {
        if (print)
            cout << "next string: " << s << "\n";
        try {
            sum += stoi(s);
            if (print)
                cout << "  added to sum!\n";
        } catch (...) {
            if (print)
                cout << "  the last string was not an integer :(\n";
            continue;
        }
    }
    cout << "Sum of integers in file (" << inputfile << "): " << sum << "\n";
}

int main() {
    exercise_01();
    exercise_11();
    return 0;
}