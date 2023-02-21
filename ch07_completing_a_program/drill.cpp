
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.


Drill
-----

 1. Starting from the file calculator08buggy.cpp, get the calculator to compile.
 
    (1) 
    drill.cpp: In member function ‘Token Token_stream::get()’:
    drill.cpp:113:24: error: no matching function for call to ‘Token::Token(const char&, std::__cxx11::string&)’
        return Token(name, s);

    Issue -- Token class did not have constructor with (char, string) as arguments!


 2. Go through the entire program and add appropriate comments.

    TODO


 3. As you commented, you found errors (deviously inserted especially for you to find).
    Fix them; they are not in the text of the book.

    I think I found them all??


 4. Testing: prepare a set of inputs and use them to test the calculator.
    Is your list pretty complete? What should you look for?
    Include negative values, 0, very small, very large, and “silly” inputs.
 
    1) Test all digits (0-9, and '.')
    2) Test positive / negative unary operator
    3) Test multiplication, division, modulus of two numbers
        - for division / mod: try zero as second operand!  Should get helpful error
    4) Test addition, subtraction of two numbers
    5) Test order of operations with three numbers
        no parens (combo of + - and / % *)
E       with parens
E   6) Test variables 
        - Set (first time), should work
        - Try re-defining same variable (should get error)
        - Print out the variable value
        - Try using variable in two-operand expression
        - Try setting variable equal to an expression
        - Try updating variable's value (idk if this is allowed in spec??)
    7) Quit

    Bad inputs:
    



 5. Do the testing and fix any bugs that you missed when you commented.
 
 6. Add a predefined name k meaning 1000.
 
 7. Give the user a square root function sqrt(), for example, sqrt(2+6.7).
    Naturally, the value of sqrt(x) is the square root of x; for example, sqrt(9) is 3.
    Use the standard library sqrt() function that is available through the header std_lib_facilities.h.
    Remember to update the comments, including the grammar.
 
 8. Catch attempts to take the square root of a negative number and print an appropriate error message.
 
 9. Allow the user to use pow(x,i) to mean “Multiply x with itself i times”; for example, pow(2.5,3) is 2.5*2.5*2.5.
    Require i to be an integer using the technique we used for %.

10. Change the “declaration keyword” from let to #.

11. Change the “quit keyword” from quit to exit.
    That will involve defining a string for quit just as we did for let in §7.8.2.

*/

#include "../std_lib_facilities.h"

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
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
    case quit:  // L: this was not here!
    case print:
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
        cin.unget();
        double val;
        cin >> val;
        return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s = ch;
			cin.unget();
			if (s == "let") return Token(let);
			if (s == "quit") return Token(quit); // L: should return quit, not 'name'
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

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
// Set value of existing variable
{
    // L:                vv should be less than, not leq!
    // for (int i = 0; i <= names.size(); ++i)
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");  // L: misleading print statement '(' vs ')'
	}
	case '-':
		return -primary();
    // the below case was not here
    case '+':
        return primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
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
            if (t.kind == '%') left = fmod(left, d); // L: new!
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

double declaration()
// string name -> string varname
// I don't like that it's same name as the const char used for t.kind
// Somehow, the compiler doesn't complain though?
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");  // L: now using constant
	string varname = t.name;
	if (is_declared(varname)) error(varname, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", varname);
	double d = expression();
	names.push_back(Variable(varname, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
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