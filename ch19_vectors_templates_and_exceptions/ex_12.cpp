/*
12. Define a File_handle class with a constructor that takes a string argument (the file name), 
    opens the file in the constructor, and closes it in the destructor.
*/

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class File_handle {
    fstream f;
public:
    File_handle (string filepath) {
        f.open(filepath, ios_base::in | ios_base::out);
        if (!f)
            throw runtime_error("Error: could not open file for input (" + filepath + ")");
    };
    ~File_handle () { f.close(); }
    // making the class useful by exposing some of `f`'s functionality
    string read() {
        auto size = f.tellg();
        string contents(size, '\0');
        f.seekg(0); // go to front
        if (f.read(&contents[0], size))
            return contents;
        return "";
    }
    void write(string contents) {
        if (contents.size() == 0)
            return;
        f.write(contents.c_str(), contents.size());
    }
};