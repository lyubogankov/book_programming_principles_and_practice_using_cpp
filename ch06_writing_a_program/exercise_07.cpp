/*
 7. Write a grammar for bitwise logical expressions. 
 
    A bitwise logical expression is much like an arithmetic expression except that the operators are 
    ! (not), ~ (complement), & (and), | (or), and ^ (exclusive or).
    
    Each operator does its operation to each bit of its integer operands (see §25.5). ! and ~ are prefix unary operators.
    
    A ^ binds tighter than a | (just as * binds tighter than +) so that x|y^z means x|(y^z) rather than (x|y)^z.
    
    The & operator binds tighter than ^ so that x^y&z means x^(y&z).

*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr char EXIT_CHAR = 'q';
constexpr char PRINT_CHAR = ';';

//------------------------------------------------------------------------------

class Token{
public:
    char kind;
    string value;
    Token(char ch)
        :kind(ch), value("") {}
    Token(char ch, string s)
        :kind(ch), value(s) {}
};

//------------------------------------------------------------------------------

// copying directly from book / drill
class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

Token_stream::Token_stream()
    :full(false), buffer(0) { }

void Token_stream::putback(Token t)
{
    if (full) throw runtime_error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case PRINT_CHAR:  // for "print"
    case EXIT_CHAR:   // for "quit"
    case '(': case ')': 
    case '!': case '~':
    case '&': case '^': case '|':
        return Token(ch);        // let each character represent itself
    case '0': case '1':
    {
        string binary_str = "";
        binary_str += ch;
        while(true) {
            cin >> ch;
            if (ch != '0' && ch != '1') {
                cin.putback(ch);
                return Token('b', binary_str); // 'b' represents binary string
            }
            binary_str += ch;
        }
    }
    default:
        throw runtime_error("Bad token");
    }
}

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------
 
/*
grammar hierarchy

expression:
    op_or
op_or:
    op_xor
    op_or "|" op_xor
op_xor:
    op_and
    op_xor "^" op_and
op_and:
    unary_prefix
    op_and "&" unary_prefix
unary_prefix:
    binary_string
    "!" binary_string
    "~" binary_string
binary_string:
    string of 0s and/or 1s
    "(" expression ")"
*/

string expression(); // function signature

string binary_string() {
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        string s = expression();
        t = ts.get();                        // v  ERROR 3/5 -- missing close-quote
        if (t.kind != ')') throw runtime_error("')' expected");
            return s;
    }
    case 'b':            // we use 'b' to represent a binary string
        return t.value;  // return the binary string
    default:
        throw runtime_error("primary expected");
    }
}
string unary_prefix() {
    Token t = ts.get();
    while(true) {
        switch(t.kind) {
        case '!': case '~': {
            string old_str = binary_string();
            string new_str = "";
            // perform negation
            for (char c  : old_str) {
                if      (c == '0') new_str += '1';
                else if (c == '1') new_str += '0';
            }
            return new_str;
        }
        // // Not sure what '~' is supposed to do?  2's complement?  1's complement = negation...
        // case '~': {
        //     string bin_str = binary_string();
        //     // perform complement
        //     return bin_str;
        // }
        case 'b':
            return t.value;
        }
    }
}
string create_zero_string(int size) {
    string zero_string = "";
    for (int i=0; i < size; i++)
        zero_string += '0';
    return zero_string;
}
string op_and() {
    string left = unary_prefix();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '&': {
            string right = unary_prefix();
            // loop over the two strings, perform operation on the last n bits, where n = min(str1_len, str2_len)
            string result = "";

            // append leading 0s to smaller binary string
            int size_diff = abs(int(left.size()) - int(right.size()));
            if (left.size() > right.size()) {
                // result = left.substr(0, size_diff);
                // left   = left.substr(size_diff);
                right = create_zero_string(size_diff) + right;
            } else if (right.size() > left.size()) {
                // result = right.substr(0, size_diff);
                // right  = right.substr(size_diff);
                left = create_zero_string(size_diff) + left;
            }

            // cout << result << "\n";

            // at this point, left/right should be the same size
            for (int i=0; i < left.size(); i++) {
                if (left[i] == '1' && right[i] == '1')
                    result += '1';
                else
                    result += '0';
            }
            
            // in case there are more &s, we need to put result -> left.
            left = result;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}
string op_xor() {
    string left = op_and();
    return left;
}
string op_or() {
    string left = op_xor();
    return left;
}
string expression() {
    string left = op_or();
    return left;
}

//------------------------------------------------------------------------------

int main() {

    cout << "Bitwise operation calculator:\n"
         << "Please enter binary numbers (consisting of 0s and 1s)."
         << "Valid operators:\n"
         << "    !  (negation)\n"
         << "    ~  (complement)\n"
         << "    &  (and)\n"
         << "    ^  (xor)\n"
         << "    |  (or)\n"
         << "   ( ) (parentheses)\n"
         << "To evaluate expression, type '" << PRINT_CHAR << "'\n"
         << "To exit calculator, type '" << EXIT_CHAR << "'\n\n";

    string bin_str = "";
    while(cin) {
        Token t = ts.get();
        if (t.kind == EXIT_CHAR) break;
        if (t.kind == PRINT_CHAR)
            cout << '=' << bin_str << "\n\n";
        else {
            ts.putback(t);
            bin_str = expression();
        }
    }

    return 0;
}