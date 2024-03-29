/*
 12. Reverse the order of characters in a text file. 
    For example, asdfghjkl becomes lkjhgfdsa. 
    Warning: There is no really good, portable, and efficient way of reading a file backward.

13. Reverse the order of words (defined as whitespace-separated strings) in a file. 
    For example, Norwegian Blue parrot becomes parrot Blue Norwegian. 
    You are allowed to assume that all the strings from the file will fit into memory at once.
*/

#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void ex12(const string& src="ex_12-13_input.txt", const string& dst="ex_12_output.txt") {
    // Can I do this by manipulating the file pointer?  Try it!
    /*  It worked!!

    Input

this is a file of whitespace-separated
words.  Notice how there was a newline  there?  And then a tab, and two spaces.
    
    Output

.secaps owt dna ,bat a neht dnA  ?ereht  enilwen a saw ereht woh ecitoN  .sdrow
detarapes-ecapsetihw fo elif a si siht
    */

    ifstream ifs {src};
    if (!ifs) throw runtime_error("Could not open file for reading (" + src + ")");
    ofstream ofs {dst};
    if (!ofs) throw runtime_error("Could not open file for writing (" + dst + ")");

    /*
    https://en.cppreference.com/w/cpp/io/basic_istream/seekg
    https://en.cppreference.com/w/cpp/io/basic_istream/tellg
    https://en.cppreference.com/w/cpp/io/ios_base/seekdir
    */
    // // beginning = 0, end = 118 = size.
    // ifs.seekg(0, ios_base::beg);
    // cout << "Beginning position: " << ifs.tellg() << "\n";
    // ifs.seekg(0, ios_base::end);
    // int _size = ifs.tellg();
    // cout << "End position:       " << _size << "\n";
    
    ifs.seekg(0, ios_base::end);
    int size = ifs.tellg();
    char c;
    for(int i=1; i <= size; i++) {
        ifs.seekg(-1*i, ios_base::end); // position pointer
        ifs >> noskipws >> c;
        // cout << "[" << i << "]  " << c << "  " << int(c) << "\n";
        ofs << c;
    }
}

void ex13_ignorewhitespace(const string& src="ex_12-13_input.txt", const string& dst="ex_13_output.txt") {
    // This function will reverse the order, but it will not preserve the type of whitespace
    // encountered between words.  In the output, all words will be separated by space (' ').
    //
    // In order to preserve type of whitespace, need to read in the file contents character-by-character.
    /*
    Input

this is a file of whitespace-separated
words.  Notice how there was a newline  there?  And then a tab, and two spaces.

    Output

spaces. two and tab, a then And there? newline a was there how Notice words. whitespace-separated of file a is this

    */


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
void ex13_preserve_whitespace(const string& src="ex_12-13_input.txt", const string& dst="ex_13_output2.txt") {
    /*
    Input

this is a file of whitespace-separated
words.  Notice how there was a newline  there?  And then a tab, and two spaces.

    Output
    
spaces. two and tab, a then And  there?  newline a was there how Notice  words.
whitespace-separated of file a is this
    */

    ifstream ifs {src};
    if (!ifs) throw runtime_error("Could not open file for reading (" + src + ")");
    ofstream ofs {dst};
    if (!ofs) throw runtime_error("Could not open file for writing (" + dst + ")");

    vector<string> contents;
    char c;
    string s;
    while (ifs >> noskipws >> c) {
        // if we've encountered a whitespace char we know we're done with current
        // word stored in s.  Also store the whitespace!
        if (isspace(c)) {
            contents.push_back(s);
            s = ""; // reset s
            string ws {c};
            contents.push_back(ws);
        } else
            s.push_back(c);
    }
    if (s.size() > 0)
        contents.push_back(s);

    for(int i=contents.size()-1; i >= 0; i--)
        ofs << contents[i];
}

int main() {
    ex12();
    ex13_ignorewhitespace();
    ex13_preserve_whitespace();
    return 0;
}