/*
1. Write a program that reads a text file and converts its input to all lower case, producing a new file.
*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void filetolower(string srcfile = "ex_01_input.txt", string destfile = "ex_01_output.txt") {
    ifstream ifs {srcfile};
    if (!ifs) {
        cout << "Could not open file for reading (" << srcfile << ")\n";
        return;
    }
    ofstream ofs {destfile};
    if (!ofs) {
        cout << "Could not open file for writing (" << destfile << ")\n";
        return;
    }
    char c;
    while(ifs >> noskipws >> c)
        ofs << (char)tolower(c);
}

int main() {
    filetolower();
    return 0;
}