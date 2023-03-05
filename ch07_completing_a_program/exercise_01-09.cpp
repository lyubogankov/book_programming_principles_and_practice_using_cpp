
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

	- Defined const char for representing constant token's kind
	- Defined const string for constant keyword ("const")
	- Added new if clause to Token_stream::get()'s default case to detect constant keyword
	- declaration() now takes a bool argument that is passed into Variable instantiation to make it constant or not
	- statement() now sends declaration() t.kind == constant (aka, are we making a const or var)


4. The get_value(), set_value(), is_declared(), and define_name() functions all operate on the variable names (vector<Variable>).
   Define a class called Symbol_table with a member var_table of type vector<Variable> and member functions get(), set(), is_declared(), and declare().
   Rewrite the calculator to use a variable of type Symbol_table.

	- Defined Symbol_table class
	- Moved functionality for get_value(), set_value(), is_declared() into it
	- Created declare() function, which just replaces the names.push_back() in order to create variables
		(This decouples the creation of variables from the underlying data structure)


5. Modify Token_stream::get() to return Token(print) when it sees a newline.
   This implies looking for whitespace characters and treating newline ('\n') specially.
   You might find the standard library function isspace(ch),
   which returns true if ch is a whitespace character, useful.

	Change 1: use "noskipws" stream format specifier for cin to keep whitespace
	Change 2: eat non-newline whitespace
	Change 3: return Token(print) when we encounter a newline


6. Part of what every program should do is to provide some way of helping its user.
   Have the calculator print out some instructions for how to use the calculator if the user presses the H key (both upper- and lowercase).
7. Change the q and h commands to be quit and help, respectively.

	Done!  For #6, added additional cases to check for 'h'/'H' within Token_stream::get()
		   and changed the logic within calculator_REPL():

	```diff
	 while (true) try {
	 	cout << prompt;
	 	Token t = ts.get();
	 	while (t.kind == print) t = ts.get();
	 	if (t.kind == quit) return;
	- 	ts.unget(t);
	- 	cout << result << statement() << endl;	
	+ 	if (t.kind == help) 
	+ 		print_help();
	+ 	else {
	+ 		ts.unget(t);
	+ 		cout << result << statement() << endl;
	+ 	}
	 }
	```

	#7 - I removed the case for 'h'/'H' within Token_stream::get() 
		 and implemented a check in the default case instead.


8. The grammar in §7.6.4 is incomplete (we did warn you against overreliance on comments); 
   it does not define sequences of statements, such as 4+4; 5–6;, 
   and it does not incorporate the grammar changes outlined in §7.8. 
   Fix that grammar. Also add whatever you feel is needed to that comment 
   as the first comment of the calculator program and its overall comment.

   # ex: 4+4; 5-6; help 2*3; q
		 ^^^                     Calculation -> Statement -> Expression
		    ^                    Calculation -> Print
			  ^^^                Calculation -> Statement -> Expression
				 ^               Calculation -> Print
				   ^^^^          Calculation -> Help
					    ^^^      Calculation -> Statement -> Expression
						   ^     Calculation -> Print
							 ^   Calculation -> Quit


9. Suggest three improvements (not mentioned in this chapter) to the calculator. Implement one of them.

	1. User-defined functions that take in a specified number of floating-point inputs,
	   evaluate an expression and return a float!

	   	Could re-implement sqrt() and pow() as pre-defined functions
		Allow functions to be over-written (no "const", unlike some variables)

		Grammar update (just showing relevant portions).  I think this covers it?
		This way I can:
			- Assign a function to a variable
			- Overwrite assignment (either with a new Function, or an Expression)
			- Execute a function by calling its variable with appropriate arguments

			Declaration:
				"let" Name '=' Expression		// or "#"
				"const" Name '=' Expression
		*		"let" Name '=' Function
		*	Function:
		*		"lambda" ArgList':' Expression
		*	ArgList:
		*		''								// empty
		*		Name
		*		ArgList',' Name
			...
			Primary:
				Number
				Variable								// existing variable bound to number, but this is checked at runtime
				Variable '=' Expression					// existing variable, but this is checked at runtime
		*		Variable '=' Function					// existing variable, but this is checked at runtime
				'(' Expression ')'
				"sqrt"'(' Expression ')'
				"pow"'(' Expression ',' Integer ')'
		*		Variable(ArgList)						// existing variable bound to function, but this is checked at runtime
				'-'Primary
				'+'Primary

		Additionally, I would need to:
			- Create a Function class
			- Expand the Symbol_table to allow a double OR a Function class in the Vector.
				Idk if that's possible in a single Vector, maybe I'd need two.


	2. Command (statement? expression?) history from current session.
	   User presses UP /DOWN arrows to select command from history, can rerun it!

	   	What to define as history?  In command prompt, it's delimited by ENTER
		Maybe build up a string of the user's input, and add it to an array when they press ENTER?
		Then, when they press UP/DOWN arrows, display those onto std out as options?  Not sure how to overwrite small portions of screen, though.
		Then, when they select a prior command to execute, need to feed that cin for normal processing.


	3. Support for hexadecimal numbers
		  Input from user:
			a. Investigate whether cin >> float supports hex.  If so, how to enable? (Tried, not by default)
			b. Any other solutions in c++ std lib or online?  this is not a new problem
			c. Write my own cin -> hex parser?
		  Conversion between dec <-> hex
		  Implicit conversion to dec (?) if mixed representations are used?
		  	What does Python do about this?  I can mix just find, dec is returned by default.

*/

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
	Floating-point number (can be float or integet)
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
	double declare(string v, double d, bool readonly);
	double get(string v);
	void set(string v, double d);
	bool is_declared(string v);
};
double Symbol_table::declare(string v, double d, bool readonly) {
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
		 << "Please enter expressions using floating point numbers.\n"
		 << "Valid operators:\n"
		 << "        +      (addition)\n"
		 << "        -      (subtraction)\n"
		 << "        *      (multiplication)\n"
		 << "        /      (division)\n"
		 << "       ( )     (parentheses) \n"
		 << "    pow(b, n)  (b = base, n = exponent)\n"
		 << "    sqrt(x)    (square root of non-negative x)\n"
		 << "To evaluate expression, type '" << print << "' or press ENTER\n"
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
			cout << result << statement() << endl;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	calculator_REPL();
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