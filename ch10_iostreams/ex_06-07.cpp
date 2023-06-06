/*
6. Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
    Provide Roman_int with an as_int() member that returns the int value,
    so that if r is a Roman_int, we can write cout << "Roman" << r << " equals " << r.as_int() << '\n';.

7. Make a version of the calculator from Chapter 7 that 
    accepts Roman numerals rather than the usual Arabic ones, for example, XXI + CIV == CXXV.
*/

#include <iostream>
using namespace std;

class Roman_int {
    public:
        Roman_int()      : value {0} {}
        Roman_int(int x) : value {x} {}
        int as_int() const { return value; }
    private:
        int value;
};
// M = 1000, D = 500, C = 100, L = 50, X = 10, V = 5, I = 1
ostream& operator<<(ostream& os, const Roman_int& r) {
    int value = r.as_int();

    int thousands = value / 1000;
    value -= thousands*1000;

    int fivehundreds = value / 500;
    value -= fivehundreds*500;

    int onehundreds = value / 100;
    value -= onehundreds*100;

    int fifties = value / 50;
    value -= fifties*50;

    int tens = value / 10;
    value -= tens*10;

    int fives = value / 5;
    value -= fives*5;

    // at this point, value should equal "ones"
    cout << "value: " << r.as_int() << "\n"
         << "1000s: " << thousands << "\n"
         << " 500s: " << fivehundreds << "\n"
         << " 100s: " << onehundreds << "\n"
         << "  50s: " << fifties << "\n"
         << "  10s: " << tens << "\n"
         << "   5s: " << fives << "\n"
         << "   1s: " << value << "\n";

    // from document: when writing a numeral express each part of the number as if it were written
    //                in expanded notation.  Ex: 65 = 60 + 5;  827 = 800 + 20 + 7
    //  Also, a single numeral cannot repeat more than 3 times.

    return os;
}
// M = 1000, D = 500, C = 100, L = 50, X = 10, V = 5, I = 1
const int NO_NUMERAL = 0;
int roman_to_int(int previous_numeral, int current_numeral, bool final_numeral, bool debugprint=true) {
    if (debugprint)
        cout << "  prev: " << previous_numeral << "  curr: " << current_numeral << "\n";
    // handling a single numeral (no previous numeral)
    if (previous_numeral == NO_NUMERAL) {
        if (final_numeral) return current_numeral;
        else               return 0;
    }
    // left < right means subtraction
    if (previous_numeral < current_numeral)
        return current_numeral - previous_numeral;
    // otherwise, just return the current numeral
    return current_numeral;
}
istream& operator>>(istream& is, Roman_int& r) {
    
    int current_numeral = NO_NUMERAL;
    int previous_numeral = NO_NUMERAL;
    int total = 0;
    int numerals_seen = 0;

    char ch;
    bool breakout = false;
    while(is >> ch) {
        numerals_seen++;
        previous_numeral = current_numeral;
        switch (ch) {
            case 'M':
                current_numeral = 1000;
                break;
            case 'D':
                current_numeral = 500;
                break;
            case 'C':
                current_numeral = 100;
                break;
            case 'L':
                current_numeral = 50;
                break;
            case 'X':
                current_numeral = 10;
                break;
            case 'V':
                current_numeral = 5;
                break;
            case 'I':
                current_numeral = 1;
                break;
            default:
                breakout = true;
        }
        if (breakout)
            break;
        // now that we have a numeral, decide what its integer value is!
        total += roman_to_int(previous_numeral, current_numeral, false);
    }
    // finish out the conversion
    total += roman_to_int(previous_numeral, current_numeral, true);
    r = Roman_int(total);

    return is;
}

void test_roman_int() {
    // //      these are all numbers that satisfy left-to-right rule
    // cout << Roman_int(2) << "\n"
    //      << Roman_int(20) << "\n"
    //      << Roman_int(102) << "\n"
    //      << Roman_int(660) << "\n"
    // //      these don't!
    //      << Roman_int(9) << "\n"
    //      << Roman_int(24) << "\n"
    //      << Roman_int(299) << "\n"
    //      << Roman_int(1947) << "\n";

    bool quit = false;
    while (!quit) {
        cout << "Please type roman numerals followed by ENTER.  Press 'CTRL+C' to quit.\n";
        Roman_int r;
        cin >> r;
        cout << "  as int: " << r.as_int() << "\n\n";
    }
}


int main() {
    test_roman_int();
    return 0;
}