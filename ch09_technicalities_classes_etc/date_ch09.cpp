#include <iostream>
using namespace std;

#include "date_ch09.h" // for ex09

ostream& operator<<(ostream& os, const Month& m) { return os << int(m); }

Date::Date(int yy, Month mm, int dd) {
    if (1 <= int(mm) && int(mm) <= 12 && 1 <= dd && dd <= 31) {
        y = yy;
        m = mm;
        d = dd;
    } else {
        throw InvalidDate();
    }
}
void Date::add_day(int n) {
    if (d + n <= 31) {
        d += n;
    } else {
        m = Month(int(m) + (d + n) / 31);
        d = (d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, const Date& d) {
    return os << "Date(y=" << d.year() << ", m=" << d.month() << ", d=" << d.day() << ")";
}