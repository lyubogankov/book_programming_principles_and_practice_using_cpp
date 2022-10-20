#include<iostream>
#include<string>
using namespace std;

int main() {
    cout << "Type the names of digits [0, 4], or anything else.  CTRL+D to exit.\n\n";
    string userinput;
    while(cin >> userinput)
        if (userinput == "zero")
            cout << "0\n";
        else if (userinput == "one")
            cout << "1\n";
        else if (userinput == "two")
            cout << "2\n";
        else if (userinput == "three")
            cout << "3\n";
        else if (userinput == "four")
            cout << "4\n";
        else
            cout << "... not a number I know.\n";
    return 0;
}
