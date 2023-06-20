/*
10. Write a function vector<string> split(const string& s) 
    that returns a vector of whitespace-separated substrings from the argument s.

11. Write a function vector<string> split(const string& s, const string& w) 
    that returns a vector of whitespace-separated substrings from the argument s, 
    where whitespace is defined as “ordinary whitespace” plus the characters in w.
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string& s) {
    istringstream iss {s};
    vector<string> split;
    string substr;
    while(iss >> substr)
        split.push_back(substr);
    return split;
}


bool string_contains_char(const string& s, const char& c) {
    for( char _c : s)
        if (_c == c)
            return true;
    return false;
}

vector<string> split(const string& s, const string& w) {
    // This function "splits" in a similar manner to Python's `str.split(delimiter)` function.
    // Ex (Python): `"meeeme.split('e') == ['m', '', '', 'm', '']"
    //    (C++)   :  vector output = {"m", "", "", "m", ""}
    // (see third printout)
    vector<string> split = {""};
    istringstream iss {s};
    char c;
    int current_idx = 0;
    while (iss >> noskipws >> c) {
        if (string_contains_char(w, c) || isspace(c)) {
            current_idx++;
            split.push_back("");
        } else
            split[current_idx].push_back(c);
    }
    return split;
}

int main() {

    string original_string = "this is a whitespace separated-string\nwoah\twhoosh";
    
    // using first function
    cout << "original: " << original_string << "\n";
    cout << "split:   |";
    vector<string> split_string = split(original_string);
    for (string& substr : split_string)
        cout << substr << "|";
    cout << "\n\n";

    // using second function
    cout << "original: " << original_string << "\n";
    cout << "split:   |";
    vector<string> split_string_two = split(original_string, "aeiou");
    for (string& substr : split_string_two)
        cout << substr << "|";
    cout << "\n\n";

    string og = "meeeme";
    cout << "original: " << og << "\n";
    cout << "split:   |";
    vector<string> splitog = split(og, "e");
    for (string& substr : splitog)
        cout << substr << "|";
    cout << "\n\n";    

    return 0;
}