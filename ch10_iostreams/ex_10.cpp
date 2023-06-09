/*
10. Add a command `from x` to the calculator from Chapter 7 that makes it take input from a file x.
        Brainstorming:
            What if someone types: "from file.txt; 1 + 1;" ?
            Need to somehow have a second Token_stream specifically for my file.

            Maybe I can edit the Token_stream class and have multiple input streams?
            The global one can be initialized with cin by default.

    Add a command `to y` to the calculator that makes it write its output (both standard output and error output) to file y.
        Done!  Implemented within:
        - Token_stream::get(): recognizes "to" command and filename (must end in "".txt")
        - calculator_REPL():   upon reception of "to" token, obtains filename and redirects stdout/err for x1 statement()
    
    ---
    Write a collection of test cases based on ideas from §7.3 and use that to test the calculator.
    Discuss how you would use these commands for testing.
*/


// Calculator code from Ch07:

/* Grammar
----------

Calculation:
    Statement
    Print (';') (ENTER)
    Quit ('q') (quit)
    Help (h) (help)
    from Filename (contains Statement)
    to Filename Statement
    Calculation Statement
Statement:
    Declaration
    Expression
Declaration:
    "let" Variable '=' Expression
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
    Floating-point number (can be float or integer)

Variable
    [a-zA-Z\w][a-zA-Z0-9]*    // (from drill)
    [a-zA-Z\w][a-zA-Z0-9\w]*  // (#1 -- allow underscores )
Filename
    [a-zA-Z\w][a-zA-Z0-9\w]*.txt
*/

#include "../std_lib_facilities.h"

#include <fstream>
#include <stdio.h>

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
const char filefrom = 'I';
const string filefrom_command = "from";
const char fileto = 'O';
const string fileto_command = "to";
const char filename = 'F';

const char quit = 'q';
const string quit_full = "exit";
const char help = 'h';
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
    // eat whitespace
    // https://en.cppreference.com/w/cpp/string/byte/isspace (the table really helped)
    do { cin >> noskipws >> ch; } while(isspace(ch) and ch != '\n');
    switch (ch) {
    case '\n': 
        // https://stackoverflow.com/a/15905343
        // https://en.cppreference.com/w/cpp/io/manip/skipws
        return Token(print);
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
    case help:
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
        if (isalpha(ch) || ch == '_') {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '.')) s += ch;
            cin.unget();
            if (s == "pow") return Token(_pow);
            if (s == "sqrt") return Token(_sqrt);
            if (s == quit_full) return Token(quit);
            if (s == help_full) return Token(help);
            if (s == fileto_command) return Token(fileto);
            if (s == filefrom_command) return Token(filefrom);
            if (s == const_declaration) return Token(constant);
            if (s == var_declaration) return Token(let);
            // adding for filename: needs to end in .txt
            if (s.find(".txt") == s.size() - 4) return Token(filename, s);
            // variables are not allowed to have a period within them
            if (s.find('.') == -1) return Token(name, s);
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
         << "Please enter expressions using integers and/or floating point numbers.\n"
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
    symbol_table.declare("pi", 3.1415926535, true);

    while (true) try {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();
        if (t.kind == quit) return;

        // redirect output (stdout, stderr) to a file
        if (t.kind == fileto) {
            // obtain output file
            t = ts.get();
            if (t.kind != filename) error("expected filename after 'to' keyword");
            string fileout = t.name;
            // check whether the file can be opened
            ofstream ofs {fileout};
            if (!ofs) throw runtime_error("Could not open file for output (" + fileout + ")");
            ofs.close(); // close explicitly
            // perform redirection
            freopen(fileout.c_str(), "w", stdout);
            freopen(fileout.c_str(), "w", stderr);
            // output computation
            cout << statement() << '\n';
            // revert redirection
            freopen("/dev/tty", "w", stdout);
            freopen("/dev/tty", "w", stderr);
        }
        // otherwise, print to the screen as usual!
        else {
            if (t.kind == help) 
                print_help();
            else {
                ts.unget(t);
                cout << result << statement() << '\n';
            }
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