/*
8. Write a program that accepts two file names
    and produces a new file that is the contents of the first file 
    followed by the contents of the second; 
    that is, the program concatenates the two files.
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void copy_file_contents(string source, ofstream& ofs_dest) {
    ifstream ifs_source {source};
    if (!ifs_source) throw runtime_error("Could not open file for reading: " + source);
    string input;
    // https://stackoverflow.com/a/16410153 (getline, ignoring newline in buffer)
    //  Ignoring newline in buffer turned out to be detrimental?  Not sure what's up with the recommendation
    while(getline(ifs_source, input))
        ofs_dest << input << "\n";
}
void concatenate(string fileone = "ex_01.txt", string filetwo = "ex_11.txt", string output = "ex_08.txt") {
    ofstream ofs {output};
    if (!ofs) throw runtime_error("Could not open file for writing: " + output);
    copy_file_contents(fileone, ofs);
    copy_file_contents(filetwo, ofs);
}

int main() {
    concatenate();
    return 0;
}