/*
 12. Reverse the order of characters in a text file. 
    For example, asdfghjkl becomes lkjhgfdsa. 
    Warning: There is no really good, portable, and efficient way of reading a file backward.

13. Reverse the order of words (defined as whitespace-separated strings) in a file. 
    For example, Norwegian Blue parrot becomes parrot Blue Norwegian. 
    You are allowed to assume that all the strings from the file will fit into memory at once.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void ex13(const string& src="ex_12-13_input.txt", const string& dst="ex_13_output.txt") {
    // This function will reverse the order, but it will not preserve the type of whitespace
    // encountered between words.  In the output, all words will be separated by space (' ').
    ifstream ifs {src};
    if (!ifs) throw runtime_error("Could not open file for reading (" + src + ")");
    ofstream ofs {dst};
    if (!ofs) throw runtime_error("Could not open file for writing (" + dst + ")");
    
    vector<string> contents;
    string s;
    while(ifs >> s)
        contents.push_back(s);

    for(int i=contents.size()-1; i >= 0; i--) {
        ofs << contents[i];
        if (i > 0)
            ofs << ' ';
    }
}

int main() {

    ex13();

    return 0;
}