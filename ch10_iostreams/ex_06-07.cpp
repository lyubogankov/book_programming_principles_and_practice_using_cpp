/*
6. Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
    Provide Roman_int with an as_int() member that returns the int value,
    so that if r is a Roman_int, we can write cout << "Roman" << r << " equals " << r.as_int() << '\n';.

7. Make a version of the calculator from Chapter 7 that 
    accepts Roman numerals rather than the usual Arabic ones, for example, XXI + CIV == CXXV.
*/

#include <iostream>
#include <string>
using namespace std;

const bool TEST_PRINT = false;

// https://www.hunter.cuny.edu/dolciani/pdf_files/brushup-materials/reading-and-writing-roman-numerals.pdf
class Roman_int {
    public:
        Roman_int()      : value {0} {}
        Roman_int(int x) : value {x} {}
        int as_int() const { return value; }
    private:
        int value;
};

string power_of_ten_to_roman(int leading_digit, int exponent) {
    // ex: 
    //  exponent              =  2  ( 100)
    //  exponent numeral      = 'C'
    //  next exponent         =  3  (1000)
    //  next exponent numeral = 'M'
    //  midpoint numeral      = 'D' ( 500)    
    char exponent_numeral, next_exp_numeral, midpoint_numeral;
    switch(exponent) {
        case 0:
            exponent_numeral = 'I';
            next_exp_numeral = 'X';
            midpoint_numeral = 'V';
            break;
        case 1:
            exponent_numeral = 'X';
            next_exp_numeral = 'C';
            midpoint_numeral = 'L';
            break;
        case 2:
            exponent_numeral = 'C';
            next_exp_numeral = 'M';
            midpoint_numeral = 'D';
            break;
    }
    
    string output = "";
    // [1, 3]
    if (leading_digit < 4) {
        for (int i=0; i<leading_digit; i++) output.push_back(exponent_numeral);
    }
    // 4 
    else if (leading_digit == 4) {
        output.push_back(exponent_numeral);
        output.push_back(midpoint_numeral);
    }
    // 9
    else if (leading_digit == 9) {
        output.push_back(exponent_numeral);
        output.push_back(next_exp_numeral);
    }
    // [5, 8]
    else {
        output.push_back(midpoint_numeral);
        for (int i=0; i<(leading_digit - 5); i++) output.push_back(exponent_numeral);
    }
    return output;
}
ostream& operator<<(ostream& os, const Roman_int& r) {
    // from document: when writing a numeral express each part of the number as if it were written
    //                in expanded notation.  Ex: 65 = 60 + 5;  827 = 800 + 20 + 7
    //  Also, a single numeral cannot repeat more than 3 times.
    
    int ones = r.as_int();

    int thousands = ones / 1000;
    ones -= thousands*1000;
    int onehundreds = ones / 100;
    ones -= onehundreds*100;
    int tens = ones / 10;
    ones -= tens*10;

    if (TEST_PRINT)
        cout << "value: " << r.as_int() << "\n"
            << "1000s: " << thousands << "\n"
            << " 100s: " << onehundreds << "\n"
            << "  10s: " << tens << "\n"
            << "   1s: " << ones << "\n";

    string output = "";
    // not handling anything above 3000
    if (thousands > 0)
        for (int i=0; i<thousands; i++) output.push_back('M');
    if (onehundreds > 0)
        output += power_of_ten_to_roman(onehundreds, 2);
    if (tens > 0)
        output += power_of_ten_to_roman(tens, 1);
    if (ones > 0)
        output += power_of_ten_to_roman(ones, 0);

    return os << output;
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

void test_roman_input() {
    while (true) {
        cout << "Please type roman numerals followed by ENTER.  Press 'CTRL+C' to quit.\n";
        Roman_int r;
        cin >> r;
        cout << "  as int: " << r.as_int() << "\n\n";
    }
}
void test_roman_output() {
    //      these are all numbers that satisfy left-to-right rule
    cout << "  2: " << Roman_int(2) << "\n"
         << " 20: " <<  Roman_int(20) << "\n"
         << "102: " <<  Roman_int(102) << "\n"
         << "660: " <<  Roman_int(660) << "\n"
    //      these don't!
         << "   9: " <<  Roman_int(9) << "\n"
         << "  24: " <<  Roman_int(24) << "\n"
         << " 299: " <<  Roman_int(299) << "\n"
         << "2307: " <<  Roman_int(2307) << "\n"
    // more examples     
         << "  65: " <<  Roman_int(65) << "\n"
         << "  49: " <<  Roman_int(49) << "\n"
         << " 345: " <<  Roman_int(345) << "\n"
         << " 827: " <<  Roman_int(827) << "\n";
}


int main() {
    test_roman_output();
    test_roman_input();
    return 0;
}