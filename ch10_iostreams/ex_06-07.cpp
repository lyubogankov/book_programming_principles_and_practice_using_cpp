/*
6. Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
    Provide Roman_int with an as_int() member that returns the int value,
    so that if r is a Roman_int, we can write cout << "Roman" << r << " equals " << r.as_int() << '\n';.

7. Make a version of the calculator from Chapter 7 that 
    accepts Roman numerals rather than the usual Arabic ones, for example, XXI + CIV == CXXV.


    Plan: change the `Number` within the grammar to accept Roman numerals.
        This involves modifying `Token_stream::get()`, which handles input from the user.

    Question: should I use my `Roman_int` class as a way to get a raw integer into the calculator,
                or should the calculator operate directly on `Roman_int`s?

    Complication:
        If the calc is to operate directly on `Roman_int`s, I need to write operator overloads.
        However, that won't be sufficient, because idk if I can overload `sqrt()` and `pow()`.

        Also, several operations (division, sqrt, pow) have the potential to return a non-integer
        output.  Thankfully integer division is defined, but I'll need to cast the result 
        of sqrt/pow to integer.

    Finally:
        Will need to also use `Roman_int` class for output to screen.


    ---

    Changes:
    - Token_stream::get() - re-defining what is a valid number
    - calculator_REPL()   - at the very end, casting the printout of statement() as a Roman_int when printing  
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
    is.unget(); // will this put back the last char? it seems to be eating characters
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

// ================================================================================================
// ================================================================================================
// Calculator code from Ch07:

/* Grammar
----------

Calculation:
    Statement
    Print (';') (ENTER)
    Quit ('q') (quit)
	Help (h) (H) (help)
    Calculation Statement  #8 -- recursively allowing sequences of statements in the grammar.
Statement:
    Declaration
    Expression
Declaration:
    "let" Variable '=' Expression		// or "#"
	"const" Variable '=' Expression
Expression:
    Term
    Expression '+' Term
    Expression '-' Term
Term:
    Primary
    Term '*' Primary
    Term '/' Primary
    Term '%' Primary
Primary:
    Number
	Existing_Variable
	Existing_Variable '=' Expression
    '(' Expression ')'
	"sqrt"'(' Expression ')'
	"pow"'(' Expression ',' Integer ')'
    '-'Primary
    '+'Primary
Number
	Roman numeral (only uppercase letters) // Floating-point number (can be float or integer)

Variable
	[a-zA-Z][a-zA-Z0-9]*  // (from drill)
	[a-zA-Z]\w*			  // (#1 -- allow underscores )
*/

#include "../std_lib_facilities.h"

// ------------------------------------------------------------------------------------------------
struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch, string s) :kind(ch), name(s) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char);
};

const char let = 'L';
const string var_declaration = "let";
const char constant = 'C';
const string const_declaration = "const";
const char quit = 'q';
const string quit_full = "exit";
const char help = 'h';
const char help_upper = 'H';
const string help_full = "help";
const char print = ';';
const char number = '8';
const char name = 'a';
const char _sqrt = 's';
const char _pow = 'p';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	// # 5
	// eat whitespace
	// https://en.cppreference.com/w/cpp/string/byte/isspace (the table really helped)
	do { cin >> noskipws >> ch; } while(isspace(ch) and ch != '\n');
	switch (ch) {
	case '\n': 
		// https://stackoverflow.com/a/15905343
		// https://en.cppreference.com/w/cpp/io/manip/skipws
		return Token(print);
	// // #6
	// case help:
	// case help_upper:
	// 	return Token(help);
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':   // L: added for pow(x, i)
    case quit:
    case print:
		return Token(ch);
	// case '.':
	// case '0':
	// case '1':
	// case '2':
	// case '3':
	// case '4':
	// case '5':
	// case '6':
	// case '7':
	// case '8':
	// case '9':
    case 'M':
    case 'D':
    case 'C':
    case 'L':
    case 'X':
    case 'V':
    case 'I':
	{	
        cin.unget();
        Roman_int val; // double val;
        cin >> val;
        return Token(number, val.as_int());
	}
	default:
		// the OR clause feels hacky.  Not sure how it's "supposed" to be done.
		// #1
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;  // #1
			cin.unget();
			if (s == "pow") return Token(_pow);
			if (s == "sqrt") return Token(_sqrt);
			if (s == quit_full) return Token(quit);
			if (s == help_full) return Token(help);  // # 7
			if (s == var_declaration) return Token(let);
			if (s == const_declaration) return Token(constant);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

// ------------------------------------------------------------------------------------------------

struct Variable {
	string name;
	double value;
	bool readonly;
	Variable(string n, double v) :name(n), value(v), readonly(false) { }
	Variable(string n, double v, bool ro) :name(n), value(v), readonly(ro) { }
};

class Symbol_table {
	vector<Variable> var_table;
public:
	Symbol_table() :var_table({}) { }
	void declare(string v, double d, bool readonly);
	double get(string v);
	void set(string v, double d);
	bool is_declared(string v);
};
void Symbol_table::declare(string v, double d, bool readonly) {
	var_table.push_back(Variable(v, d, readonly));
}
double Symbol_table::get(string v) {
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == v) return var_table[i].value;
	error("get: undefined name ", v);
}
void Symbol_table::set(string v, double d) {
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == v) {
			if (var_table[i].readonly == true) error("Cannot set value to constant variable ", v);
			var_table[i].value = d;
			return;
		}
	error("set: undefined name ", v);
}
bool Symbol_table::is_declared(string v) {
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == v) return true;
	return false;
}

Symbol_table symbol_table;

// ------------------------------------------------------------------------------------------------

Token_stream ts;

double expression();

void ensure_next_token_of_desired_kind(char desired, string error_msg) {
	Token t = ts.get();
	if (t.kind == desired) return;
	ts.unget(t);
	error(error_msg);
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
        double d = expression();
		ensure_next_token_of_desired_kind(')', "')' expected");
		return d;
	}
	case '-':
		return -primary();
    case '+':
        return primary();
	case number:
		return t.value;
	case name: {
		string varname = t.name;
		Token t2 = ts.get();
		// variable lookup
		if (t2.kind != '=') {
			ts.unget(t2);
			return symbol_table.get(varname);
		}
		// variable re-assignment
		double d = expression();
		symbol_table.set(varname, d);
		return d;
	}
	case _sqrt: {
		ensure_next_token_of_desired_kind('(', "'(' expected after \"sqrt\"");
		double d = expression();
		if (d < 0) error("Cannot compute sqrt() of negative number");
		ensure_next_token_of_desired_kind(')', "')' expected to conclude sqrt()");
		return sqrt(d);
	}
	// pow(x, i) = x^i;
	case _pow: {
		ensure_next_token_of_desired_kind('(', "'(' expected after \"pow\"");
		double x = expression();
		ensure_next_token_of_desired_kind(',', "',' expected to delineate arguments of pow()");
		int i = narrow_cast<int>(expression()); // prevents info loss, will return error for non-int arg
		ensure_next_token_of_desired_kind(')', "')' expected to conclude ()");
		return pow(x, i);
	}
	default:
		cin.unget();
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
        case '%':
		{	
            double d = primary();
            if (d == 0) error("divide by zero");
            if (t.kind == '/') left /= d;
            if (t.kind == '%') left = fmod(left, d);
            break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration(bool constant)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string varname = t.name;
	if (symbol_table.is_declared(varname)) error(varname, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", varname);
	double d = expression();
	symbol_table.declare(varname, d, constant);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
	case constant:
		return declaration((t.kind == constant));
	default:
		ts.unget(t);
		return expression();
	}
}

// ------------------------------------------------------------------------------------------------

void clean_up_mess()
{
	ts.ignore(print);
}

void print_help() {
	cout << "Welcome to our simple calculator.\n"
		 << "Please enter expressions using Roman numerals (uppercase letters only).\n"
         << "Since it operates on Roman numerals, only positive integer input/output is supported."
		 << "Valid operators:\n"
		 << "        +      (addition)\n"
		 << "        -      (subtraction)\n"
		 << "        *      (multiplication)\n"
		 << "        /      (division)\n"
		 << "       ( )     (parentheses) \n"
		 << "    pow(b, n)  (b = base, n = exponent)\n"
		 << "    sqrt(x)    (square root of non-negative x)\n"
		 << "To evaluate expression, type '" << print << "' or press ENTER\n"
         << "\n"
         << "You may create named variables (read/writeable) using the following syntax:\n"
         << "    let {variable_name} = Expression  // variable names should be lowercase to avoid conflicting with Roman numerals\n"
         << "\n"
         << "You may also created named constants (read-only once created) using the following syntax:\n"
         << "    const {variable_name} = Expression\n"
         << "\n"
         << "You may bring up this help text by typing '" << help << "' at any time.\n"
		 << "To exit calculator, type '" << quit << "' or '" << quit_full << "'\n"
		 << "\n";
}

const string prompt = "> ";
const string result = "= ";

void calculator_REPL()
{
	// #3 - turning into constant
	// #4 - using Symbol_table class
	symbol_table.declare("k", 1000.0, true);

	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		if (t.kind == help) 
			print_help();
		else {
			ts.unget(t);
			cout << result << Roman_int{int(statement())} << '\n';
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << '\n';
		clean_up_mess();
	}
}

int main()
try {
    print_help();
	calculator_REPL();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}