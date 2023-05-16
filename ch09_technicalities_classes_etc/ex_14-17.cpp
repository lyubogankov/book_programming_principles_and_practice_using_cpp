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

18. Give an example of a calculation where a Rational gives a mathematically better result than double.
*/

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Money {
    public:
        // constructors
        Money(string denomination, double amount);
        // // generic term = ? whole units vs fractions/remainder as hundredth (multiplied by 100)
        // Money(string denomination, int dollars, int cents);
        Money(string denomination, int wholes, int hundredths);
        
        // accessors
        string denomination() const { return _denomination; }
        int wholes() const { return _hundredths / 100; }
        int hundredths() const { return _hundredths % 100; }
        int as_hundredths() const { return _hundredths; }
    private:
        long int _hundredths {0};
        string _denomination;
};
int fourth_fifths_round(double unrounded) {
    // odd behavior: previously had floor(amount*100), but that consistently chopped off a whole cent.
    //               I also tested int(amount*100), and it had the same effect.
    int h = int(unrounded*1000)/ 10;         // whole + hundredths
    if ((int(unrounded*1000) % 10) >= 5)     // 4/5 rounding rule
        h += 1;
    return h;
}
Money::Money(string denomination, int wholes, int hundredths) :
    _denomination {denomination},
    _hundredths { wholes*100 + hundredths }
{}
Money::Money(string denomination, double amount) : 
    _denomination {denomination},
    _hundredths {fourth_fifths_round(amount)}
{}

ostream& operator<<(ostream& os, Money m) {
    // https://stackoverflow.com/a/1714538
    return os << m.denomination() << m.wholes() << "." 
              << setfill('0') << setw(2)    // want leading zero!
              << m.hundredths()
              << setfill(' ');                // reset to default, bc apparently it's persistent
}

Money operator+(const Money& m1, const Money& m2) {

}
Money operator-(const Money& m1, const Money& m2) {

}
Money operator*(const Money& m, const int n) {

}
Money operator*(const int n, const Money& m) { return m*n; }

// not defining n / $, as that doesn't yield Money (it returns something per unit currency)
Money operator/(const Money& m, const int n) {
    return Money(
        m.denomination(), 
        fourth_fifths_round(double(m.as_hundredths()) / n)
    );
}

int main() {

    Money d1 {"$", 10.04};
    Money d2 {"$", 10, 4};
    Money d3 {"DKK", 5.123};
    Money d4 {"DKK", 5.987};

    cout << "d1: " << d1 << "\n"
         << "d2: " << d2 << "\n"
         << "d3: " << d3 << "\n"
         << "d4: " << d4 << "\n";

    return 0;
}