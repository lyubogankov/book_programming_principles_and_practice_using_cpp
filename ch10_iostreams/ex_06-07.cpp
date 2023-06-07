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

const char NO_NUMERAL = '-';
int roman_numeral_to_int(char numeral) {
    switch (numeral) {
        case 'M': return 1000;
        case 'D': return  500;
        case 'C': return  100;
        case 'L': return   50;
        case 'X': return   10;
        case 'V': return    5;
        case 'I': return    1;
        default:  return    0;
    }
}
class RomanNumeralInputBuffer {
    public:
        RomanNumeralInputBuffer() {};
        // numerals get shifted from R -> L
        //  (imagine sliding a 2-numeral window across the page from L->R; 
        //   the first window edge they encounter is the right one)
        void add_numeral_to_buffer(char new_numeral) {
            left_numeral = right_numeral;
            right_numeral = new_numeral;
        }
        int evaluate_buffer(bool final_numeral);
        void print() { cout << "l:" << left_numeral << " r:" << right_numeral << "\n"; }
    private:
        char left_numeral = NO_NUMERAL;
        char right_numeral = NO_NUMERAL;
};
int RomanNumeralInputBuffer::evaluate_buffer(bool final_numeral=false) {
    // no more numerals to process
    if (final_numeral) {
        if (right_numeral != NO_NUMERAL)
            return roman_numeral_to_int(right_numeral);
        else
            return roman_numeral_to_int(left_numeral);
    }
    // first numeral in buffer, but not necessarily the last
    if (left_numeral == NO_NUMERAL)
        return 0;
    // otherwise, we have two numerals in the buffer that need processing!
    // subtraction
    int right_int = roman_numeral_to_int(right_numeral);
    int left_int  = roman_numeral_to_int(left_numeral);
    if (left_int < right_int) {
        left_numeral = NO_NUMERAL;
        right_numeral = NO_NUMERAL;
        return right_int - left_int;
    }
    // regular - just process left numeral as-is
    return left_int;
}
const bool TEST_PRINT = false;
istream& operator>>(istream& is, Roman_int& r) {
    RomanNumeralInputBuffer buffer {};
    int result = 0;
    int total = 0;
    char ch;
    while(is >> ch) {
        if (TEST_PRINT)
            cout << "current char: " << ch << "\n";
        if (ch != 'M' && ch != 'D' && ch != 'C' && ch != 'L' && ch != 'X' && ch != 'V' && ch != 'I')
            break;
        if (TEST_PRINT) {
            cout << "  before: ";
            buffer.print();
        }
        buffer.add_numeral_to_buffer(ch);
        if (TEST_PRINT) {
            cout << "  after:  ";
            buffer.print();
            result = buffer.evaluate_buffer();
            cout << "  result: " << result << "\n";
            total += result;
        } else
            total += buffer.evaluate_buffer();
    }
    // finish out the conversion
    total += buffer.evaluate_buffer(true);
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