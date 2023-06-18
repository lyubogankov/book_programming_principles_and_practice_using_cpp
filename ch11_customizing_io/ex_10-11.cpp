/*
10. Write a function vector<string> split(const string& s) 
    that returns a vector of whitespace-separated substrings from the argument s.

11. Write a function vector<string> split(const string& s, const string& w) 
    that returns a vector of whitespace-separated substrings from the argument s, 
    where whitespace is defined as “ordinary whitespace” plus the characters in w.
*/

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

// vector<string> split(const string& s, const string& w) {

// }

int main() {

    string original_string = "this is a whitespace separated-string\nwoah\twhoosh";
    cout << "original: " << original_string << "\n";
    cout << "split:   |";
    vector<string> split_string = split(original_string);
    for (string& substr : split_string)
        cout << substr << "|";
    cout << "\n";

    return 0;
}