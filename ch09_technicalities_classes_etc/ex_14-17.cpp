/*
14. Design and implement a Money class for calculations involving dollars and cents
    where arithmetic has to be accurate to the last cent using the 4/5 rounding rule
    (.5 of a cent rounds up; anything less than .5 rounds down).
    
    Represent a monetary amount as a number of cents in a long int, but input and output as dollars and cents, e.g., $123.45.
    Do not worry about amounts that don’t fit into a long int.

15. Refine the Money class by adding a currency (given as a constructor argument).
    Accept a floating-point initializer as long as it can be exactly represented as a long int.
    
    Don’t accept illegal operations. For example, Money*Money doesn’t make sense, and USD1.23+DKK5.00 makes sense only if
    you provide a conversion table defining the conversion factor between U.S. dollars (USD) and Danish kroner (DKK).

16. Define an input operator (>>) that reads monetary amounts with currency denominations, such as USD1.23 and DKK5.00, into a Money variable.
    Also define a corresponding output operator (<<).

Discussion qs
-------------

17. Give an example of a calculation where a Rational gives a mathematically better result than Money.

    Rational: (1/3) + (1/3) = (2/3)       = 0.6666666...  // most correct answer
    Money:    (1/3) + (1/3) = 0.33 + 0.33 = 0.66          // each 1/3 rounded down (4/5 rule). error: +0.00666...
    Money:            (2/3)               = 0.67          //      2/3 rounded up   (4/5 rule). error: -0.00333...

18. Give an example of a calculation where a Rational gives a mathematically better result than double.

    Irrational fractions.
    Rational: (1/77) = 0.012987012987012987012987...  (according to Wolfram Alpha)
    Double:   (1/77) = 0.01298701298701299           (according to storing in a double and printing using the code below)
                                         ^^^^^^^^...  
    ```C++
    #include <iostream>
    #include <limits>
    using namespace std;
    //         0.012987012987012988
    double d = 0.01298701298701298701298701298701298701298701298701298701298701298701298701298701298701298701298701299;
    int main() {
        cout.precision(numeric_limits<double>::max_digits10);
        cout << std::fixed << d << "\n";
        return 0;
    }
    ```
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const bool DEBUG_PRINT = false;

// The only supported currencies for conversion are USD, DKK, JPY.
// However, will omit error checking for this exercise.
string USD = "$";
string DKK = "DKK";
string JPY = "¥";
enum class conv_idx { UNKNOWN=-1, USD, DKK, JPY };
conv_idx assign_conversion_idx(string denomination) {
    if (denomination == USD) return conv_idx::USD;
    if (denomination == DKK) return conv_idx::DKK;
    if (denomination == JPY) return conv_idx::JPY;
    return conv_idx::UNKNOWN;
}
// lookup: outer conv_idx = from, inner conv_idx = to
//  ex: USD -> DKK = CONVERSION_TABLE[conv_idx::USD][conv_idx::DKK] = CONVERSION_TABLE[0][1]
vector<vector<double>> CONVERSION_TABLE { 
    {1.0000, 6.8800, 137.4200}, // USD to...
    {0.1453, 1.0000,  19.9600}, // DKK to...
    {0.0073, 0.0500,   1.0000}  // JPY to...
}; // rates on 2023-05-17

class Money {
    public:
        // constructors
        Money() {};
        Money(string denomination, double amount);
        // // generic term = ? whole units vs fractions/remainder as hundredth (multiplied by 100)
        // Money(string denomination, int dollars, int cents);
        Money(string denomination, int wholes, int hundredths);
        
        // accessors
        string denomination() const { return _denomination; }
        int wholes() const { return _hundredths / 100; }
        int hundredths() const { return _hundredths % 100; }
        int as_hundredths() const { return _hundredths; }
        conv_idx conversion_idx() const { return _conversion_idx; }
        int cidx() const { return int(_conversion_idx); }
        
        // error reporting
        class InvalidSyntax {};
        class UnsupportedConversion {};
    private:
        long int _hundredths {0};
        string _denomination {""};
        conv_idx _conversion_idx {conv_idx::UNKNOWN};
};
int fourth_fifths_round(double unrounded) {
    // odd behavior: previously had floor(amount*100), but that consistently chopped off a whole cent.
    //               I also tested int(amount*100), and it had the same effect.
    int thousandths = int(unrounded*1000);
    int h = thousandths / 10;         // whole + hundredths
    // THIS WAS MY SUBTRACTION BUG!  no abs(), and no sign-based adjustment
    if (abs(thousandths % 10) >= 5) {    // 4/5 rounding rule
        if (thousandths < 0) h -= 1;
        else                 h += 1;
    }
    if (DEBUG_PRINT)
        cout << "\n"
             << "        fourth_fifths_round(" << unrounded << ")\n"
             << "              unrounded*1000     = " <<     unrounded*1000     << "\n"
             << "          int(unrounded*1000)    = " << int(unrounded*1000)    << "\n"
             << "          int(unrounded*1000)/10 = " << int(unrounded*1000)/10 << "\n"
             << "          int(unrounded*1000)%10 = " << int(unrounded*1000)%10 << "\n"
             << "          abs(int(unrounded*1000)%10) >= 5? " << (abs(int(unrounded*1000)%10) >= 5) << "\n"
             << "                      hundredths = " << h << "\n";
    return h;
}
Money::Money(string denomination, int wholes, int hundredths) :
    _denomination {denomination},
    _hundredths { wholes*100 + hundredths },
    _conversion_idx {assign_conversion_idx(denomination)}
{}
Money::Money(string denomination, double amount) : 
    _denomination {denomination},
    _hundredths {fourth_fifths_round(amount)},
    _conversion_idx {assign_conversion_idx(denomination)}
{}

ostream& operator<<(ostream& os, Money m) {
    // https://stackoverflow.com/a/1714538
    if (m.as_hundredths() < 0)
        os << "-";
    return os << m.denomination() << abs(m.wholes()) << "." 
              << setfill('0') << setw(2)    // want leading zero!
              << abs(m.hundredths())
              << setfill(' ');                // reset to default, bc apparently it's persistent
}
istream& operator>>(istream& is, Money& m) {
    // if is enters bad() state, throw exception
    is.exceptions(is.exceptions() | ios_base::badbit);

    // process characters until we see start of amount
    int count = 0;
    bool negative = false;
    string currency = "";
    for(char c; is >> c;) {
        if (isdigit(c) || c == '.') {
            is.unget();
            break;
        }
        if (c == '-') {
            if (count == 0) negative = true;
            else throw Money::InvalidSyntax();  // we only expect negative sign at the very front
        } else
            currency.push_back(c);
        count += 1;
    }
    // now, process the amount!
    double amount;
    is >> amount;
    if (!is) return is;

    if (negative) amount *= -1;
    m = Money(currency, amount);
    return is;
}

Money operator*(const Money& m, const int n) {
    if (DEBUG_PRINT)
        cout << "\n"
             << "        operator*\n"
             << "          " << m << " * " << n << "\n"
             << "           m.as_hundredths()              = " << m.as_hundredths() << "\n"
             << "          (m.as_hundredths() * n) / 100.0 = " << (m.as_hundredths() * n) / 100.0 << "\n";
    return Money(
        m.denomination(),
        (m.as_hundredths() * n) / 100.0
    );
}
Money operator*(const int n, const Money& m) { return m*n; }
Money operator*(const Money& m, const double n) {
    if (DEBUG_PRINT)
        cout << "\n"
             << "        operator*\n"
             << "          " << m << " * " << n << "\n"
             << "           m.as_hundredths()              = " << m.as_hundredths() << "\n"
             << "          (m.as_hundredths() * n) / 100.0 = " << (m.as_hundredths() * n) / 100.0 << "\n";
    return Money(
        m.denomination(),
        (m.as_hundredths() * n) / 100.0
    );
}
Money operator*(const double n, const Money& m) { return m*n; }

// not defining n / $, as that doesn't yield Money (it returns something per unit currency)
Money operator/(const Money& m, const int n) {
    return Money(
        m.denomination(), 
        fourth_fifths_round(double(m.as_hundredths()) / (n*100)) / 100.0
    );
}
Money operator/(const Money& m, const double n) {
    return Money(
        m.denomination(), 
        fourth_fifths_round(double(m.as_hundredths()) / (n*100)) / 100.0
    );
}

// Throws error if either argument has an unknown / unsupported currency type (for conversion)
void ensure_convertability(const Money& m1, const Money& m2) {
    if (m1.conversion_idx() == conv_idx::UNKNOWN || m2.conversion_idx() == conv_idx::UNKNOWN)
        throw Money::UnsupportedConversion();
}
bool operator==(const Money& m1, const Money& m2) {
    if (DEBUG_PRINT)
        cout << "\n        operator==(" << m1 << ", " << m2 << ")\n";
    if (m1.denomination() == m2.denomination())
        return (m1.as_hundredths() == m2.as_hundredths());
    if (m1.conversion_idx() == conv_idx::UNKNOWN || m2.conversion_idx() == conv_idx::UNKNOWN)
        return false;
    // convert to same denomination as m1, and then do comparison
    // choose the conversion factor greater than 1 to preserve rounding
    double m1_to_m2 = CONVERSION_TABLE[m1.cidx()][m2.cidx()];
    if (DEBUG_PRINT)
        cout << "          m1->m2 factor: " << m1_to_m2 << "\n";
    if (m1_to_m2 > 1) {
        Money m1_converted = m1 * m1_to_m2;
        if (DEBUG_PRINT)
            cout << "          m1*m1_to_m2 = " << m1_converted.wholes() << "." << m1_converted.hundredths() << "\n";
        Money m1_as_m2denom {
            m2.denomination(),
            m1_converted.wholes(),
            m1_converted.hundredths()
        };
        return m1_as_m2denom == m2;
    }
    double m2_to_m1 = CONVERSION_TABLE[m2.cidx()][m1.cidx()];
    Money m2_converted = m2 * m2_to_m1;
    if (DEBUG_PRINT)
            cout << "          m2->m1 factor: " << m2_to_m1 << "\n"
                 << "          m2*m2_to_m1 = " << m2_converted.wholes() << "." << m2_converted.hundredths() << "\n";
    Money m2_as_m1denom {
        m1.denomination(),
        m2_converted.wholes(),
        m2_converted.hundredths()
    };
    return m1 == m2_as_m1denom;
        
}
Money operator+(const Money& m1, const Money& m2) {
    if (DEBUG_PRINT)
        cout << "\n"
             << "        operator+(" << m1 << ", " << m2 << ")\n";
    // same denomination: perform addition!
    if (m1.denomination() == m2.denomination())
        return Money(
            m1.denomination(), 
            m1.wholes() + m2.wholes(), 
            m1.hundredths() + m2.hundredths()
        );
    ensure_convertability(m1, m2);
    // otherwise, there's conversion required.  Always return denomination of m1.
    double m2_to_m1 = CONVERSION_TABLE[m2.cidx()][m1.cidx()];
    Money m2_converted = m2 * m2_to_m1;
    if (DEBUG_PRINT)
        cout << "          conversion factor, m2 -> m1 currency: " << m2_to_m1 << "\n"
             << "          m2 converted: " << m2_converted.wholes() << "." << m2_converted.hundredths() << "\n";
    return Money(
        m1.denomination(),
        m1.wholes() + m2_converted.wholes(),
        m1.hundredths() + m2_converted.hundredths()
    );
}
Money operator-(const Money& m1, const Money& m2) {
    if (DEBUG_PRINT)
        cout << "\n        operator-(" << m1 << ", " << m2 << ")\n";
    return m1 + (-1 * m2);
}

int main() {

    Money d1 {USD, 10.04};
    Money d2 {USD, 10, 4};
    Money d3 {DKK, 5.123};
    Money d4 {DKK, 5.987};
    Money y5 {JPY, 1100};

    // these *should* all be equal?
    Money d6 {USD, 1.00};
    Money d7 {DKK, 6.88};
    Money y8 {JPY, 137.42};

    // testing object construction, printing operator
    cout << "d1: " << d1 << "\n"
         << "d2: " << d2 << "\n"
         << "d3: " << d3 << "\n"
         << "d4: " << d4 << "\n"
         << "y5: " << y5 << "\n"
         << "Money(USD,  1, -5): " << Money(USD, 1, -5) << "\n"
         << "Money(USD, -1,  5): " << Money(USD, -1, 5) << "\n" 
         << "Money(USD, -0.95):  " << Money(USD, -0.95) << "\n\n";


    // testing multiplication, division by constant
    cout << "d1 / 2: " << d1 / 2 << "\n"
         << "d1 * 2: " << d1 * 2 << "\n"
         << "(d1*2) == (2*d1): " << ((d1 * 2) == (2 * d1)) << "\n"
         << "d1 * 1.23: " << d1 * 1.23 << "\n\n";

    // testing equality
    cout << "d6: " << d6 << "\n"
         << "d7: " << d7 << "\n"
         << "y8: " << y8 << "\n"
         << "d6 == d6:" << (d6 == d6) << "\n"
         << "d6 == d7:" << (d6 == d7) << "\n"
         << "d7 == d6:" << (d7 == d6) << "\n"
         << "d6 == y8:" << (d6 == y8) << "\n"
         << "d2 == y8:" << (d2 == y8) << "\n\n";

    // testing addition, subtraction
    cout << "d1 + d1: " << d1 + d1 << "\n"
         << "(d1 + d1) == (d1 * 2): " << ((d1 + d1) == (d1 * 2)) << "\n"
         << "d6 + d7: " << d6 + d7 << "\n"
         << "d7 + d6: " << d7 + d6 << "\n"
         // there's a rounding error in the subtraction...
         << "d6 - d7: " << d6 - d7 << "\n"    //   $0.01
         << "d7 - d6: " << d7 - d6 << "\n\n"; // DKK0.00

    // testing input operator
    while (true) {
        Money m;
        cout << "    Input a Money: ";
        cin >> m;
        cout << "    Here is the Money you entered: " << m << "\n";
    }

    return 0;
}