
/*
1. Allow underscores in the calculator’s variable names.

   Changed Token_stream::get() to allow underscore within initial if (first character) and subsequent characters.
   Valid variable names: "_", "_x", "x_", "_x_", etc.


2. Provide an assignment operator, =, so that you can change the value of a variable after you introduce it using let.
   Discuss why that can be useful and how it can be a source of problems.

   Done during drill.
   Useful so that we can reuse variables
   Source of problems = ? (because we may forget which variable has which value??
   						   to me this is not a sufficient problem to justify not having the feature)


3. Provide named constants that you really can’t change the value of.
   Hint: You have to add a member to Variable that distinguishes between constants and variables and check for it in set_value().
   If you want to let the user define constants (rather than just having pi and e defined as constants),
   you’ll have to add a notation to let the user express that, for example, const pi = 3.14;.




4. The get_value(), set_value(), is_declared(), and define_name() functions all operate on the variable var_table.
   Define a class called Symbol_table with a member var_table of type vector<Variable> and member functions get(), set(), is_declared(), and declare().
   Rewrite the calculator to use a variable of type Symbol_table.




5. Modify Token_stream::get() to return Token(print) when it sees a newline.
   This implies looking for whitespace characters and treating newline ('\n') specially.
   You might find the standard library function isspace(ch), which returns true if ch is a whitespace character, useful.




6. Part of what every program should do is to provide some way of helping its user.
   Have the calculator print out some instructions for how to use the calculator if the user presses the H key (both upper- and lowercase).




7. Change the q and h commands to be quit and help, respectively.




8. The grammar in §7.6.4 is incomplete (we did warn you against overreliance on comments); it does not define sequences of statements, such as 4+4; 5–6;, and it does not incorporate the grammar changes outlined in §7.8. Fix that grammar. Also add whatever you feel is needed to that comment as the first comment of the calculator program and its overall comment.

9. Suggest three improvements (not mentioned in this chapter) to the calculator. Implement one of them.

*/

/* Grammar
----------

Calculation:
    Statement
    Print (';')
    Quit ('q')
    Calculation Statement
Statement:
    Declaration
    Expression
Declaration:
    "let" Name '=' Expression		// or "#"
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
	Floating-point number (can be float or integet)
Variable
	[a-zA-Z][a-zA-Z0-9]*  // (from drill)
	[a-zA-Z]\w*			  // (#1 -- allow underscores )
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
const string var_declaration = "let";
const char quit = 'q';
const string quit_full = "exit";
const char print = ';';
const char number = '8';
const char name = 'a';
const char _sqrt = 's';
const char _pow = 'p';

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
	case ',':   // L: added for pow(x, i)
    case quit:
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
			if (s == var_declaration) return Token(let);
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
			return get_value(varname);
		}
		// variable re-assignment
		double d = expression();
		set_value(varname, d);
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

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
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
	names.push_back(Variable("k", 1000.0));

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